#ifndef PBRICK_LIGHT_H
#define PBRICK_LIGHT_H

#ifdef __cplusplus
extern "C" {
#endif

#include "pbrick_board.h"

#if !defined(PBRICK_LIGHT_LEFT_FRONT) || !defined(PBRICK_LIGHT_RIGHT_FRONT) || !defined(PBRICK_LIGHT_HIGH)
#error "PBRICK_LIGHT_LEFT_FRONT, PBRICK_LIGHT_RIGHT_FRONT, or PBRICK_LIGHT_HIGH is not defined. Check your board definition."
#endif

/**@brief Initializes lighting
 *
 * @return      void
 */
void pbrick_light_init();

/**@brief Sets the lighting
 *
 * @param[in] uint8_t[] data    Event data
 *
 * @return void
 */
void pbrick_light_set(const uint8_t option[]);

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

/**@brief Custom disconnection event
 *
 * @return void
 */
void pbrick_light_ble_disconnect();

/**@brief Custom connection event
 *
 * @return void
 */
void pbrick_light_ble_connect();

/**@brief Blinks the right side lights
 *
 * @return void
 */
void pbrick_light_right_blink();

/**@brief Blinks the specified lights aT `delay` ms
 *
 * @param[in]       lights[]      An array of lights
 * @param[in]       count         Size of lights[]
 *
 * @return void
 */
void pbrick_light_blink(uint32_t lights[], uint8_t count);

/**@brief Sets the light option for the given light
 *
 * @param[in]       lights[]    The light to toggle
 * @param[in]       count       Size of lights[]
 * @param[in]       option      The option to perform
 *
 * @return void
 */
void pbrick_light_do_option(uint32_t lights[], uint8_t count, uint8_t option);

#ifdef __cplusplus
}
#endif

#endif // PBRICK_LIGHT_H