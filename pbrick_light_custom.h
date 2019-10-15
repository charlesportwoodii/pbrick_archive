#ifndef PBRICK_LIGHT_CUSTOM_H
#define PBRICK_LIGHT_CUSTOM_H

#ifdef __cplusplus
extern "C" {
#endif

#include "pbrick_board.h"

/**@brief Initialize custom lighting profile
 *
 * @return void
 */
void pbrick_light_custom_init();

/**@brief Set a custom lighting profile directly from BLE
 *
 * @param[in] uint8_t[]     option      The option to set
 * @return void
 */
void pbrick_light_custom_set(const uint8_t option[]);

/**@brief Custom connection event
 *
 * @return void
 */
void pbrick_light_ble_connect();

/**@brief Custom disconnection event
 *
 * @return void
 */
void pbrick_light_ble_disconnect();

#ifdef __cplusplus
}
#endif

#endif // PBRICK_LIGHT_CUSTOM_H