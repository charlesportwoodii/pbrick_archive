#include "app_pwm.h"
#include "nrf_gpio.h"
#include "nrf_delay.h"
#include "pbrick_motor.h"
#include "pbrick_board.h"

APP_PWM_INSTANCE(PWM0, 1);

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
}

void pbrick_motor0_set(uint8_t direction, uint8_t pwm)
{
    int speed = (int)pwm;
    if (speed > 100) {
        speed = 100;
    }

    while (app_pwm_channel_duty_set(&PWM0, 0, abs(speed)) == NRF_ERROR_BUSY);
    if (direction == 0x00) {
        pbrick_motor0_forward();
    } else if (direction == 0x01) {
        pbrick_motor0_reverse();
    }
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