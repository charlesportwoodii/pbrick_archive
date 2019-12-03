#ifndef BLE_PBRICK_H__
#define BLE_PBRICK_H__

#include <stdint.h>
#include <stdbool.h>
#include "ble.h"
#include "ble_srv_common.h"

#ifdef __cplusplus
extern "C" {
#endif

/**@brief   Macro for defining ble_pbrick instance
 *
 * @param   _name   Name of the instance.
 * @hideinitializer
 */
#define BLE_PBRICK_DEF(_name) \
static ble_pbrick_t _name; \
NRF_SDH_BLE_OBSERVER(_name ## _obs, \
                     BLE_HRS_BLE_OBSERVER_PRIO, \
                     ble_pbrick_on_ble_evt, &_name)

// PBrick Service UUID Base
// 0626cf96-cbce-419c-92d7-8965e276b5d2
#define PBRICK_SERVICE_UUID_BASE {{0xD2, 0xB5, 0x76, 0xE2, 0x65, 0x89, 0xD7, 0x92, 0x9C, 0x41, 0xCE, 0xCB, 0x96, 0xCF, 0x26, 0x06}}

#define PBRICK_SERIVCE_UUID     0x7062

#define PBRICK_MOTOR_CHAR_UUID  0x7063
#define PBRICK_LIGHT_CHAR_UUID  0x7064

/**@brief Custom Service init structure.
 *        This contains all options and data needed for
 *        initialization of the service.
 */
typedef struct
{
    // Initial security level for Custom characteristics attribute
    ble_srv_cccd_security_mode_t  motor_char_attr_md;
    ble_srv_cccd_security_mode_t  lights_char_attr_md;
} ble_pbrick_init_t;

/**@brief Custom Service structure.
 *        This contains various status information for the service.
 */
struct ble_pbrick_s
{
    // Handle of Custom Service (as provided by the BLE stack)
    uint16_t                      service_handle;

    // Handles related to the Custom Value characteristic.
    ble_gatts_char_handles_t      motor_value_handles;
    ble_gatts_char_handles_t      lights_value_handles;

    // Handle of the current connection (as provided by the BLE stack, is BLE_CONN_HANDLE_INVALID if not in a connection).
    uint16_t                      conn_handle;
    uint8_t                       uuid_type;
};

typedef struct ble_pbrick_s ble_pbrick_t;

/**@brief Function for initializing the Custom Service.
 *
 * @param[out]  p_pbrick       Custom Service structure. This structure will have to be supplied by
 *                          the application. It will be initialized by this function, and will later
 *                          be used to identify this particular service instance.
 * @param[in]   p_pbrick_init  Information needed to initialize the service.
 *
 * @return      NRF_SUCCESS on successful initialization of service, otherwise an error code.
 */
uint32_t ble_pbrick_init(ble_pbrick_t * p_pbrick, const ble_pbrick_init_t * p_pbrick_init);


/**@brief Function for adding motor control characteristic
 *
 * @param[in]   p_pbrick        Custom Service structure.
 * @param[in]   p_pbrick_init   Information needed to initialize the service.
 *
 * @return      NRF_SUCCESS on success, otherwise an error code.
 */
uint32_t motor_char_add(ble_pbrick_t * p_pbrick, const ble_pbrick_init_t * p_pbrick_init);

/**@brief Function for handling the Application's BLE Stack events.
 *
 * @details Handles all events from the BLE stack of interest to the Service
 *
 * @param[in]   p_ble_evt  Event received from the BLE stack.
 * @param[in]   p_context  Custom Service structure.
 */
void ble_pbrick_on_ble_evt(ble_evt_t const * p_ble_evt, void * p_context);

/**@brief Shutdowns GPIO pins to prevent runaway behavior.
 */
void gpio_shutdown();

#ifdef __cplusplus
}
#endif

#endif // BLE_PBRICK_H__

/** @} */