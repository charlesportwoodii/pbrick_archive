#ifndef PBRICK_PCA10059_H
#define PBRICK_PCA10059_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stdlib.h>
#include <stdint.h>
#include "nrf.h"
#include "boards.h"
#include "nrf_gpio.h"

// On board LEDS
#define PBRICK_LED1                 LED_1
#define PBRICK_LED2                 LED_2
#define PBRICK_LED3                 LED_3
//#define PBRICK_LED4                 LED_4

// Motor control
#define PBRICK_PWM0_PWM             NRF_GPIO_PIN_MAP(0, 2)
#define PBRICK_PWM0_P1              NRF_GPIO_PIN_MAP(0, 3)
#define PBRICK_PWM0_P2              NRF_GPIO_PIN_MAP(0, 31)

// LED definitions

// Highbeams
#define PBRICK_LIGHT_HIGH           NRF_GPIO_PIN_MAP(1, 21)

// Main headlights
#define PBRICK_LIGHT_LEFT_FRONT     NRF_GPIO_PIN_MAP(0, 22)
#define PBRICK_LIGHT_RIGHT_FRONT    NRF_GPIO_PIN_MAP(0, 23)

// Rear lights
//#define PBRICK_LIGHT_LEFT_REAR      NRF_GPIO_PIN_MAP(0, 23)
//#define PBRICK_LIGHT_RIGHT_REAR     NRF_GPIO_PIN_MAP(0, 2)

// Daytime running lights
//#define PBRICK_LIGHT_LOW            NRF_GPIO_PIN_MAP(0, 7)

// Accessory lighting
//#define PBRICK_LIGHT_ACC0           NRF_GPIO_PIN_MAP(0, 8)
//#define PBRICK_LIGHT_ACC1           NRF_GPIO_PIN_MAP(1, 9)
//#define PBRICK_LIGHT_ACC2           NRF_GPIO_PIN_MAP(1, 10)

#define PBRICK_AUTO_LIGHTS_ON_AT_BOOT true
#ifdef __cplusplus
}
#endif

#endif // PBRICK_PCA10059_H