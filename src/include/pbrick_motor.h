#ifndef PBRICK_MOTOR_H
#define PBRICK_MOTOR_H

#ifdef __cplusplus
extern "C" {
#endif

#include "app_pwm.h"
#include "pbrick_board.h"

// PWM ready flag
static volatile bool ready_flag;

struct s_pbrick_motor_state
{
    uint8_t id;
    uint8_t direction;
    uint8_t speed;
    uint8_t pins[2];
    uint8_t channel;
    const app_pwm_t   *driver;
};

typedef struct s_pbrick_motors
{
    uint8_t elements;
    uint8_t size;
    struct s_pbrick_motor_state motors[2];
} pbrick_motors;

/**@brief Initializes motor
 *
 * @return      void
 */
void pbrick_motor_init();

/**@brief Public interface to set a motor
 *
 * @param[in] uint8_t   data    3 byte data { motorId, speed, direction }
 *
 * @return void
 */
void pbrick_motor_set(const uint8_t data[]);

/**@brief Performs an immediate stop by shutting down input the specified instance
 *
 * @return void
 */
void pbrick_motor_stop(uint8_t motor);

/**@brief Stops all PWM instances
 *
 * @return void
 */
void pbrick_motor_stop_all();

#ifdef __cplusplus
}
#endif

#endif // PBRICK_MOTOR_H