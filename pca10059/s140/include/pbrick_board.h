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
#define PBRICK_LED4                 LED_4

// Motor control
#define PBRICK_PWM0_PWM             NRF_GPIO_PIN_MAP(0, 13)
#define PBRICK_PWM0_P1              NRF_GPIO_PIN_MAP(0, 17)
#define PBRICK_PWM0_P2              NRF_GPIO_PIN_MAP(0, 15)

// LED definitions

// Daytime running lights
#define PBRICK_LIGHT_LOW            NRF_GPIO_PIN_MAP(0, 20)

// Highbeams
#define PBRICK_LIGHT_HIGH           NRF_GPIO_PIN_MAP(1, 0)

// Main headlights
#define PBRICK_LIGHT_LEFT_FRONT     NRF_GPIO_PIN_MAP(0, 22)
#define PBRICK_LIGHT_LEFT_REAR      NRF_GPIO_PIN_MAP(0, 24)

// Rear lights
#define PBRICK_LIGHT_RIGHT_FRONT    NRF_GPIO_PIN_MAP(0, 31)
#define PBRICK_LIGHT_RIGHT_REAR     NRF_GPIO_PIN_MAP(0, 29)

// Accessory lighting
#define PBRICK_LIGHT_ACC0           NRF_GPIO_PIN_MAP(0, 2)
#define PBRICK_LIGHT_ACC1           NRF_GPIO_PIN_MAP(1, 15)
#define PBRICK_LIGHT_ACC2           NRF_GPIO_PIN_MAP(1, 13)

#ifdef __cplusplus
}
#endif

#endif // PBRICK_PCA10059_H