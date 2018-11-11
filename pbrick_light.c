#include "pbrick_light.h"
#include "pbrick_board.h"
#include "nrf_gpio.h"
#include "nrf_delay.h"

void pbrick_light_init()
{
    bsp_board_init(BSP_INIT_LEDS);
    nrf_gpio_cfg_output(PBRICK_LIGHT_LEFT_FRONT);
    nrf_gpio_cfg_output(PBRICK_LIGHT_LEFT_REAR);
    nrf_gpio_cfg_output(PBRICK_LIGHT_RIGHT_FRONT);
    nrf_gpio_cfg_output(PBRICK_LIGHT_RIGHT_REAR);
    nrf_gpio_cfg_output(PBRICK_LIGHT_LOW);
    nrf_gpio_cfg_output(PBRICK_LIGHT_HIGH);

// Accessories are defined per board
#ifdef PBRICK_LIGHT_ACC0
    nrf_gpio_cfg_output(PBRICK_LIGHT_ACC0);
#endif

#ifdef PBRICK_LIGHT_ACC1
    nrf_gpio_cfg_output(PBRICK_LIGHT_ACC1);
#endif

#ifdef PBRICK_LIGHT_ACC2
    nrf_gpio_cfg_output(PBRICK_LIGHT_ACC2);
#endif
}

void pbrick_light_set(uint8_t light, uint8_t option)
{
    if (light == 0x00 && option == 0x00) {
        pbrick_light_off();
    } else if (light == 0xFF && option == 0xFF) {
        pbrick_light_on();
    } else {
        switch (light) {
            case 0x01:  // Low lights
                pbrick_light_low(option);
                break;
            case 0x02:  // Main lighting
                pbrick_light_main(option);
                break;
            case 0x03:  // High lighting
                pbrick_light_high(option);
                break;
#ifdef PBRICK_LIGHT_ACC0
            case 0x04:  // Accessory 0
                pbrick_light_acc(PBRICK_LIGHT_ACC0, option);
                break;
#endif
#ifdef PBRICK_LIGHT_ACC1
            case 0x05:  // Accessory 1
                pbrick_light_acc(PBRICK_LIGHT_ACC1, option);
                break;
#endif
#ifdef PBRICK_LIGHT_ACC2
            case 0x06:  // Accessory 2
                pbrick_light_acc(PBRICK_LIGHT_ACC2, option);
                break;
#endif
            case 0x11: // Blink
                pbrick_light_blink_ctl(option);
                break;
            default:
                break;
        }
    }
}

void pbrick_light_off()
{
    nrf_gpio_pin_clear(PBRICK_LIGHT_LOW);
    nrf_gpio_pin_clear(PBRICK_LIGHT_HIGH);
    nrf_gpio_pin_clear(PBRICK_LIGHT_LEFT_FRONT);
    nrf_gpio_pin_clear(PBRICK_LIGHT_RIGHT_FRONT);
    nrf_gpio_pin_clear(PBRICK_LIGHT_LEFT_REAR);
    nrf_gpio_pin_clear(PBRICK_LIGHT_RIGHT_REAR);

// Accessories are defined per board
#ifdef PBRICK_LIGHT_ACC0
    nrf_gpio_pin_clear(PBRICK_LIGHT_ACC0);
#endif

#ifdef PBRICK_LIGHT_ACC1
    nrf_gpio_pin_clear(PBRICK_LIGHT_ACC1);
#endif

#ifdef PBRICK_LIGHT_ACC2
    nrf_gpio_pin_clear(PBRICK_LIGHT_ACC2);
#endif
}

void pbrick_light_on()
{
    nrf_gpio_pin_set(PBRICK_LIGHT_LOW);
    nrf_gpio_pin_set(PBRICK_LIGHT_HIGH);
    nrf_gpio_pin_set(PBRICK_LIGHT_LEFT_FRONT);
    nrf_gpio_pin_set(PBRICK_LIGHT_RIGHT_FRONT);
    nrf_gpio_pin_set(PBRICK_LIGHT_LEFT_REAR);
    nrf_gpio_pin_set(PBRICK_LIGHT_RIGHT_REAR);

// Accessories are defined per board
#ifdef PBRICK_LIGHT_ACC0
    nrf_gpio_pin_set(PBRICK_LIGHT_ACC0);
#endif

#ifdef PBRICK_LIGHT_ACC1
    nrf_gpio_pin_set(PBRICK_LIGHT_ACC1);
#endif

#ifdef PBRICK_LIGHT_ACC2
    nrf_gpio_pin_set(PBRICK_LIGHT_ACC2);
#endif
}

void pbrick_light_low(uint8_t option)
{
    uint32_t lights[] = {
        PBRICK_LIGHT_LOW
    };
    return pbrick_light_do_option(lights, option);
}

void pbrick_light_main(uint8_t option)
{
    uint32_t lights[] = {
        PBRICK_LIGHT_LEFT_FRONT,
        PBRICK_LIGHT_RIGHT_FRONT,
        PBRICK_LIGHT_LEFT_REAR,
        PBRICK_LIGHT_RIGHT_REAR,
        PBRICK_LIGHT_LOW
    };
    return pbrick_light_do_option(lights, option);
}

void pbrick_light_high(uint8_t option)
{
    uint32_t lights[] = {
        PBRICK_LIGHT_HIGH
    };
    return pbrick_light_do_option(lights, option);
}

void pbrick_light_acc(uint32_t acc, uint8_t option)
{
    uint32_t lights[] = {
        acc
    };
    return pbrick_light_do_option(lights, option);
}

void pbrick_light_blink_ctl(uint8_t option)
{
    switch (option) {
        case 0x01:
            pbrick_light_hazard_blink();
            break;
        case 0x02:
            pbrick_light_left_blink();
            break;
        case 0x03:
            pbrick_light_right_blink();
            break;
        default:
            break;
    }
}

void pbrick_light_hazard_blink()
{
    uint32_t lights[] = {
        PBRICK_LIGHT_LEFT_FRONT,
        PBRICK_LIGHT_RIGHT_FRONT,
        PBRICK_LIGHT_LEFT_REAR,
        PBRICK_LIGHT_RIGHT_REAR,
        PBRICK_LIGHT_LOW
    };
    return pbrick_light_blink(lights);
}

void pbrick_light_left_blink()
{
    uint32_t lights[] = {
        PBRICK_LIGHT_RIGHT_FRONT,
        PBRICK_LIGHT_RIGHT_REAR,
        PBRICK_LED1
    };
    return pbrick_light_blink(lights);
}

void pbrick_light_right_blink()
{
    uint32_t lights[] = {
        PBRICK_LIGHT_LEFT_FRONT,
        PBRICK_LIGHT_LEFT_REAR,
        PBRICK_LED4
    };
    return pbrick_light_blink(lights);
}

void pbrick_light_blink(uint32_t lights[])
{
    return pbrick_light_do_option(lights, 0x02);
}

void pbrick_light_do_option(uint32_t lights[], uint8_t option)
{
    uint8_t light_count = sizeof(&lights);

    switch (option) {
        case 0x00:
            for (uint8_t i = 0; i < light_count; i++) {
                nrf_gpio_pin_clear(lights[i]);
            }
            break;
        case 0x01:
            for (uint8_t i = 0; i < light_count; i++) {
                nrf_gpio_pin_set(lights[i]);
            }
            break;
        case 0x02:
            for (uint8_t i = 0; i < 6; i++) {
                for (uint8_t j = 0; j < light_count; j++) {
                    nrf_gpio_pin_toggle(lights[j]);
                }
                nrf_delay_ms(500);
            }
            break;
        default:
            break;
    }
}
