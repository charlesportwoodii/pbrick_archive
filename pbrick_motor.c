#include "app_pwm.h"
#include "nrf_gpio.h"
#include "nrf_delay.h"
#include "nrf_log.h"
#include "pbrick_motor.h"
#include "pbrick_board.h"

APP_PWM_INSTANCE(PWM0, 1);

pbrick_motor0_state m0s;

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

void pbrick_motor0_init()
{
    nrf_gpio_cfg_output(PBRICK_PWM0_P1);
    nrf_gpio_cfg_output(PBRICK_PWM0_P2);
    pbrick_motor0_forward();

    ret_code_t err_code;
    app_pwm_config_t pwm1_cfg = APP_PWM_DEFAULT_CONFIG_1CH(5000L, PBRICK_PWM0_PWM);

    // Switch the polarity of the second channel.
    pwm1_cfg.pin_polarity[0] = APP_PWM_POLARITY_ACTIVE_HIGH;

    // Initialize and enable PWM.
    err_code = app_pwm_init(&PWM0, &pwm1_cfg,pwm_ready_callback);
    APP_ERROR_CHECK(err_code);
    app_pwm_enable(&PWM0);

    m0s.direction = 1;
    m0s.speed = 0;
    NRF_LOG_INFO("Motor 0 initialized");
}

void pbrick_motor0_set(uint8_t direction, uint8_t pwm)
{
    int speed = (int)pwm;
    if (speed > 100) {
        NRF_LOG_INFO("Adjusting speed %x in excess of 100 to 100", speed)
        speed = 100;
    }

    m0s.direction = direction;
    m0s.speed = pwm;

    while (app_pwm_channel_duty_set(&PWM0, 0, abs(m0s.speed)) == NRF_ERROR_BUSY);
    if (m0s.direction == 0x00) {
        pbrick_motor0_forward();
    } else if (m0s.direction == 0x01) {
        pbrick_motor0_reverse();
    } else {
        NRF_LOG_WARNING("%X motor direction is not defined", m0s.direction);
    }

    NRF_LOG_DEBUG("Set Motor0: Direction: %X Speed: %X", m0s.direction, m0s.speed);
}

void pbrick_motor0_stop()
{
    NRF_LOG_WARNING("Force motor stop called.");
    app_pwm_disable(&PWM0);
    nrf_gpio_pin_clear(PBRICK_PWM0_P1);
    nrf_gpio_pin_clear(PBRICK_PWM0_P2);

    // Triggers an undefined behavior with the motor direction so the motor doesn't shift
    pbrick_motor0_set(0xFF, 0x00);
    app_pwm_enable(&PWM0);
}

void pbrick_motor0_forward()
{
    nrf_gpio_pin_clear(PBRICK_PWM0_P1);
    nrf_gpio_pin_set(PBRICK_PWM0_P2);
}

void pbrick_motor0_reverse()
{
    nrf_gpio_pin_clear(PBRICK_PWM0_P2);
    nrf_gpio_pin_set(PBRICK_PWM0_P1);
}