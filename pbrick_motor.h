#ifndef PBRICK_MOTOR_H
#define PBRICK_MOTOR_H

#ifdef __cplusplus
extern "C" {
#endif

#include "pbrick_board.h"

#if !defined(PBRICK_PWM0_P1) || !defined(PBRICK_PWM0_P1) || !defined(PBRICK_PWM0_PWM)
#error "PBRICK_PWM0_P1, PBRICK_PWM0_P2, or PBRICK_PWM0_PWM is not defined. Check your board definition."
#endif

// PWM ready flag
static volatile bool ready_flag;

/**@brief Initializes motor0
 *
 * @return      void
 */
void pbrick_motor0_init();

/**@brief Sets the motor speed
 *
 * @param[in] uint8_t   direction       The motor direction 0x00 or 0x01
 * @param[in] uint8_t   pwm             The PWM percentage to apply
 *
 * @return void
 */
void pbrick_motor0_set(uint8_t direction, uint8_t pwm);


/**@brief Performs an immediate stop by shutting down input to PWM0 and PWM1
 *
 * @return void
 */
void pbrick_motor0_stop();

/**@brief sets the motor in forward
 *
 * @return void
 */
void pbrick_motor0_forward();

/**@brief sets the motor in reverse
 *
 * @return void
 */
void pbrick_motor0_reverse();

#ifdef __cplusplus
}
#endif

#endif // PBRICK_MOTOR_H