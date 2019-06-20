#ifndef PBRICK_SPARKFUN_PRO_MINI
#define PBRICK_SPARKFUN_PRO_MINI

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

// Motor control
#ifndef PBRICK_PWM0_PWM
#define PBRICK_PWM0_PWM             NRF_GPIO_PIN_MAP(0, 2)
#endif

#ifndef PBRICK_PWM0_P1
#define PBRICK_PWM0_P1              NRF_GPIO_PIN_MAP(0, 3)
#endif

#ifndef PBRICK_PWM0_P2
#define PBRICK_PWM0_P2              NRF_GPIO_PIN_MAP(0, 31)
#endif

// LED definitions

// Highbeams
#ifndef PBRICK_LIGHT_HIGH
#define PBRICK_LIGHT_HIGH           NRF_GPIO_PIN_MAP(0, 21)
#endif

// Main headlights
#ifndef PBRICK_LIGHT_LEFT_FRONT
#define PBRICK_LIGHT_LEFT_FRONT     NRF_GPIO_PIN_MAP(0, 22)
#endif

#ifndef PBRICK_LIGHT_RIGHT_FRONT
#define PBRICK_LIGHT_RIGHT_FRONT    NRF_GPIO_PIN_MAP(0, 23)
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

#endif // PBRICK_SPARKFUN_PRO_MINI