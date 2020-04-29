#include "app_pwm.h"
#include "nrf_gpio.h"
#include "nrf_delay.h"
#include "nrf_log.h"
#include "pbrick_motor.h"
#include "pbrick_board.h"

APP_PWM_INSTANCE(PWM0, 1);

pbrick_motors motors;

/**@brief Ready callback for PWM
 *
 * @param[in] pwm_id    The PWM id
 *
 * @return      void
 */
static void pwm_ready_callback(uint32_t pwm_id)
{
    ready_flag = true;
}

/**@brief Setups a motor
 *
 * @param[in] pins      List of pins associated with the motor
 * @param[in] driver    The PWM driver to use
 * @param[in] id        The motor id used internally
 *
 * @return      void
 */
static void motor_setup(uint8_t pins[2], const app_pwm_t *driver, uint8_t id, uint8_t channel)
{
    struct s_pbrick_motor_state s;

    nrf_gpio_cfg_output(pins[0]);
    nrf_gpio_cfg_output(pins[1]);

    memcpy(s.pins, pins, 2);
    s.direction = 1;
    s.speed = 0;
    s.driver = driver;
    s.id = id;
    s.channel = channel;

    motors.motors[motors.elements] = s;
    motors.elements += 1;
}

/**@brief Setups a 3 wire configuration (PWM, IN0, IN1) for TB6612FNG or similar ICs
 *        The IN0 and IN1 are high/low, and PWM carries the PWM signal to the motor controller
 *
 * @return      void
 */
static void setup()
{
#if defined(PBRICK_PWM0_P1) && defined(PBRICK_PWM0_P2) && defined(PBRICK_PWM0_PWM)
    // If PWM0_P1 and PWM0_P2 are defined, setup that motor group
    uint8_t motor_pins[2] = { PBRICK_PWM0_P1, PBRICK_PWM0_P2 };
    motor_setup(motor_pins, &PWM0, 1, 0);
#endif

#if defined(PBRICK_PWM1_P1) && defined(PBRICK_PWM1_P2) && defined(PBRICK_PWM1_PWM)
    // If PWM1_P1 and PWM1_P2 are defined, setup that motor group
    uint8_t motor_pins2[2] = { PBRICK_PWM1_P1, PBRICK_PWM1_P2 };
    motor_setup(motor_pins2, &PWM0, 2, 1);
#endif

#if defined(PBRICK_PWM0_PWM) && defined(PBRICK_PWM1_PWM)
    // If PWM0_P1 and PWM0_P2 and PWM1_P1 and PWM1_P2 are setup, create a dual channel PWM config
    app_pwm_config_t pwm_cfg = APP_PWM_DEFAULT_CONFIG_2CH(5000L, PBRICK_PWM0_PWM, PBRICK_PWM1_PWM);
    pwm_cfg.pin_polarity[0] = APP_PWM_POLARITY_ACTIVE_HIGH;
    pwm_cfg.pin_polarity[1] = APP_PWM_POLARITY_ACTIVE_HIGH;
#else
    // If PWM0_P1 and PWM0_P2 are the only pins setup, create a single channel PWM config
    app_pwm_config_t pwm_cfg = APP_PWM_DEFAULT_CONFIG_1CH(5000L, PBRICK_PWM0_PWM);
    pwm_cfg.pin_polarity[0] = APP_PWM_POLARITY_ACTIVE_HIGH;
#endif

    ret_code_t err_code = app_pwm_init(&PWM0, &pwm_cfg, pwm_ready_callback);
    APP_ERROR_CHECK(err_code);
    app_pwm_enable(&PWM0);
}

void pbrick_motor_init()
{
    // Create mock sentinel values.
    motors.size = 2;
    motors.elements = 0;

    for (int i = 0; i < motors.size; i++) {
        motors.motors[i].id = -1;
    }

    setup();
}

void pbrick_motor_set(const uint8_t data[])
{
    uint8_t motor = data[0];
    uint8_t motorId = motors.motors[motor].id;

    // If the requested motor does not have a valid definition, abort
    if (motorId == -1) {
        NRF_LOG_INFO("Motor ID %d is not defined and settings could not be changed.", motorId);
        return;
    }

    uint8_t pwm = data[1];
    uint8_t direction = data[2];
    uint8_t channel = motors.motors[motor].channel;
    const app_pwm_t *driver = motors.motors[motor].driver;

    int speed = (int)pwm;
    if (speed > 100) {
        NRF_LOG_INFO("Adjusting speed %x in excess of 100 to 100", speed)
        speed = 100;
    }

    // Log the motor states
    motors.motors[motor].direction = direction;
    motors.motors[motor].speed = pwm;

    // For PWM0, set the channel and speed directly since PWM just controls the speed
    while (app_pwm_channel_duty_set(driver, channel, abs(motors.motors[motor].speed)) == NRF_ERROR_BUSY);


    if (direction == 0x00) {
        nrf_gpio_pin_clear(motors.motors[motor].pins[0]);
        nrf_gpio_pin_set(motors.motors[motor].pins[1]);
    } else if (direction == 0x01) {
        nrf_gpio_pin_clear(motors.motors[motor].pins[1]);
        nrf_gpio_pin_set(motors.motors[motor].pins[0]);
    } else {
        NRF_LOG_WARNING("%X motor direction is not defined", direction);
    }

    NRF_LOG_DEBUG("Set Motor %d: Direction: %X Speed: %X", motorId, direction, speed);
}

void pbrick_motor_stop(uint8_t motor)
{
    uint8_t motorId = motors.motors[motor].id;
    if (motorId == -1) {
        NRF_LOG_INFO("Unable to force stop motor due to undefined instance.");
        return;
    } else {
        NRF_LOG_INFO("Force stopping motor %d", motorId);
    }

    // Fetch the driver instance
    const app_pwm_t *driver = motors.motors[motor].driver;

    // Disable the PWM instance
    app_pwm_disable(driver);

    nrf_gpio_pin_clear(motors.motors[motor].pins[0]);
    nrf_gpio_pin_clear(motors.motors[motor].pins[1]);

    // Set the motor state
    uint8_t data[] = { motor, 0x00, 0x00 };
    pbrick_motor_set(data);

    // Re-enable the instance
    app_pwm_enable(driver);
}

void pbrick_motor_stop_all()
{
    for (int i = 0; i < motors.size; i++) {
        uint8_t motorId = motors.motors[i].id;
        if (motorId != -1) {
            pbrick_motor_stop(motorId);
        }
    }
}