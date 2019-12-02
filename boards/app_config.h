#ifndef APP_CONFIG_H
#define APP_CONFIG_H

#ifdef __cplusplus
extern "C" {
#endif

#ifdef DEBUG

#ifndef NRF_LOG_DEFAULT_LEVEL
#define NRF_LOG_DEFAULT_LEVEL 4
#endif

#ifndef NRF_LOG_BACKEND_UART_ENABLED
#define NRF_LOG_BACKEND_UART_ENABLED 1
#endif

#ifndef NRF_LOG_BACKEND_SERIAL_USES_UART
#define NRF_LOG_BACKEND_SERIAL_USES_UART 1
#endif

#ifndef NRF_SDH_BLE_LOG_LEVEL
#define NRF_SDH_BLE_LOG_LEVEL 4
#endif

#ifndef NRF_SDH_BLE_LOG_ENABLED
#define NRF_SDH_BLE_LOG_ENABLED 1
#endif

#ifndef NRF_SDH_LOG_ENABLED
#define NRF_SDH_LOG_ENABLED 1
#endif

#ifndef NRF_SDH_LOG_LEVEL
#define NRF_SDH_LOG_LEVEL 4
#endif

#endif // DEBUG

#ifdef __cplusplus
}
#endif

#endif // APP_CONFIG_H