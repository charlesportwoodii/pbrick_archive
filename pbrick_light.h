#ifndef PBRICK_LIGHT_H
#define PBRICK_LIGHT_H

#ifdef __cplusplus
extern "C" {
#endif

#include "pbrick_board.h"

/**@brief Initializes lighting
 *
 * @return      void
 */
void pbrick_light_init();

/**@brief Sets the lighting
 *
 * @param[in] uint8_t   light       The light to address
 * @param[in] uint8_t   option      Option for that light
 *
 * @return void
 */
void pbrick_light_set(uint8_t light, uint8_t option);

/**@brief Disables all lighting
 *
 * @return void
 */
void pbrick_light_off();

/**@brief Enables all lighting
 *
 * @return void
 */
void pbrick_light_on();

/**@brief Sets the options for the low lights
 *
 * @param[in]       option      The option to set
 * @return void
 */
void pbrick_light_low(uint8_t option);

/**@brief Sets the options for the main lights
 *
 * @param[in]       option      The option to set
 * @return void
 */
void pbrick_light_main(uint8_t option);

/**@brief Sets the options for the high lights
 *
 * @param[in]       option      The option to set
 * @return void
 */
void pbrick_light_high(uint8_t option);

/**@brief Sets the options for a given accessory
 *
 * @param[in]       acc         The accessory to flag
 * @param[in]       option      The option to set
 * @return void
 */
void pbrick_light_acc(uint32_t acc, uint8_t option);

/**@brief Control which lights to blink
 *
 * @param[in]       option      The option to set
 * @return void
 */
void pbrick_light_blink_ctl(uint8_t option);

/**@brief Blinks all main lights
 *
 * @return void
 */
void pbrick_light_hazard_blink();

/**@brief Blinks the left side lights
 *
 * @return void
 */
void pbrick_light_left_blink();

/**@brief Blinks the right side lights
 *
 * @return void
 */
void pbrick_light_right_blink();

/**@brief Blinks the specified lights aT `delay` ms
 *
 * @param[in]       lights[]      An array of lights
 * @return void
 */
void pbrick_light_blink(uint32_t lights[]);

/**@brief Sets the light option for the given light
 *
 * @param[in]       lights[]    The light to toggle
 * @param[in]       option      The option to perform
 * @return void
 */
void pbrick_light_do_option(uint32_t lights[], uint8_t option);

#ifdef __cplusplus
}
#endif

#endif // PBRICK_LIGHT_H