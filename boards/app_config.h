#ifndef APP_CONFIG_H
#define APP_CONFIG_H

#ifdef __cplusplus
extern "C" {
#endif

#ifdef PBRICK_DEBUG

#ifndef NRF_LOG_DEFAULT_LEVEL
#define NRF_LOG_DEFAULT_LEVEL 4
#endif

#ifndef NRF_LOG_BACKEND_UART_ENABLED
#define NRF_LOG_BACKEND_UART_ENABLED 1
#endif

#ifndef NRF_LOG_BACKEND_SERIAL_USES_UART
#define NRF_LOG_BACKEND_SERIAL_USES_UART 1
#endif

#endif // PBRICK_DEBUG

#ifdef PBRICK_CUSTOM

#ifndef PBRICK_CUSTOM_LIGHT
#define PBRICK_CUSTOM_LIGHT 1
#endif

#endif //PBRICK_CUSTOM

#ifdef __cplusplus
}
#endif

#endif // APP_CONFIG_H