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

// Motor control
#define PBRICK_PWM0_PWM         NRF_GPIO_PIN_MAP(0, 11)
#define PBRICK_PWM0_P1              NRF_GPIO_PIN_MAP(0, 3)
#define PBRICK_PWM0_P2              NRF_GPIO_PIN_MAP(0, 12)

// Motor control
#define PBRICK_PWM1_PWM         NRF_GPIO_PIN_MAP(0, 7)
#define PBRICK_PWM1_P1              NRF_GPIO_PIN_MAP(1, 9)
#define PBRICK_PWM1_P2              NRF_GPIO_PIN_MAP(1, 8)

#ifdef __cplusplus
}
#endif

#endif // PBRICK_PCA10059_H