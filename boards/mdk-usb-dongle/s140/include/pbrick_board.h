#ifndef PBRICK_MDK_USB_DONGLE_H
#define PBRICK_MDK_USB_DONGLE_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stdlib.h>
#include <stdint.h>
#include "nrf.h"
#include "boards.h"
#include "nrf_gpio.h"

// Allow overwriting and importing of custom behavior via `pbrick_custom.h` header.
#ifdef PBRICK_CUSTOM
#include "pbrick_custom.h"
#endif

// On board LEDS
#ifndef PBRICK_LED1
#define PBRICK_LED1                 LED_1
#endif

#ifndef PBRICK_LED2
#define PBRICK_LED2                 LED_2
#endif

#ifndef PBRICK_LED3
#define PBRICK_LED3                 LED_3
#endif

// Motor control
#ifndef PBRICK_PWM0_PWM
#define PBRICK_PWM0_PWM             NRF_GPIO_PIN_MAP(0, 3)
#endif

#ifndef PBRICK_PWM0_P1
#define PBRICK_PWM0_P1              NRF_GPIO_PIN_MAP(0, 2)
#endif

#ifndef PBRICK_PWM0_P2
#define PBRICK_PWM0_P2              NRF_GPIO_PIN_MAP(0, 21)
#endif
// LED definitions

// Highbeams
#ifndef PBRICK_LIGHT_HIGH
#define PBRICK_LIGHT_HIGH           NRF_GPIO_PIN_MAP(0, 4)
#endif

// Main headlights
#ifndef PBRICK_LIGHT_LEFT_FRONT
#define PBRICK_LIGHT_LEFT_FRONT     NRF_GPIO_PIN_MAP(0, 19)
#endif

#ifndef PBRICK_LIGHT_RIGHT_FRONT
#define PBRICK_LIGHT_RIGHT_FRONT    NRF_GPIO_PIN_MAP(0, 20)
#endif

#ifndef PBRICK_AUTO_LIGHTS_ON_AT_BOOT
#define PBRICK_AUTO_LIGHTS_ON_AT_BOOT 1
#endif

#ifndef PBRICK_MOTOR0_DISCONNECT_SHUTDOWN
#define PBRICK_MOTOR0_DISCONNECT_SHUTDOWN 1
#endif

#ifdef __cplusplus
}
#endif

#endif // PBRICK_MDK_USB_DONGLE_H