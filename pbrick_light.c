#include "pbrick_light.h"
#include "pbrick_board.h"
#include "nrf_gpio.h"
#include "nrf_delay.h"
#include "nrf_log.h"
#include "nrf_log_ctrl.h"

void pbrick_light_init()
{
    NRF_LOG_INFO("Initializing lighting");
    bsp_board_init(BSP_INIT_LEDS);
    nrf_gpio_cfg_output(PBRICK_LIGHT_LEFT_FRONT);
    nrf_gpio_cfg_output(PBRICK_LIGHT_RIGHT_FRONT);
    nrf_gpio_cfg_output(PBRICK_LIGHT_HIGH);

#ifdef PBRICK_LIGHT_LEFT_REAR
    nrf_gpio_cfg_output(PBRICK_LIGHT_LEFT_REAR);
    NRF_LOG_INFO("PBRICK_LIGHT_LEFT_REAR supported");
#endif
#ifdef PBRICK_LIGHT_RIGHT_REAR
    nrf_gpio_cfg_output(PBRICK_LIGHT_RIGHT_REAR);
    NRF_LOG_INFO("PBRICK_LIGHT_RIGHT_REAR supported");
#endif
#ifdef PBRICK_LIGHT_LOW
    nrf_gpio_cfg_output(PBRICK_LIGHT_LOW);
    NRF_LOG_INFO("PBRICK_LIGHT_LOW supported");
#endif

// Accessories are defined per board
#ifdef PBRICK_LIGHT_ACC0
    nrf_gpio_cfg_output(PBRICK_LIGHT_ACC0);
    nrf_gpio_cfg_output(PBRICK_LIGHT_ACC0);
    NRF_LOG_INFO("PBRICK_LIGHT_LOW supported");
#endif

#ifdef PBRICK_LIGHT_ACC1
    nrf_gpio_cfg_output(PBRICK_LIGHT_ACC1);
    NRF_LOG_INFO("PBRICK_LIGHT_ACC1 supported");
#endif

#ifdef PBRICK_LIGHT_ACC2
    nrf_gpio_cfg_output(PBRICK_LIGHT_ACC2);
    NRF_LOG_INFO("PBRICK_LIGHT_ACC2 supported");
#endif

#ifdef PBRICK_AUTO_LIGHTS_ON_AT_BOOT
    NRF_LOG_INFO("PBRICK_AUTO_LIGHTS_ON_AT_BOOT set. Enabling all available lighting.");
    pbrick_light_set(0xFF, 0xFF);
#endif
}

void pbrick_light_set(uint8_t light, uint8_t option)
{
    NRF_LOG_DEBUG("Set Lighting: Mode: %X Light: %X", light, option);
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
                NRF_LOG_WARNING("Unrecognized lighting level: %X Light: %X", light, option);
                break;
        }
    }
}

void pbrick_light_off()
{
    uint32_t lights[] = {
        PBRICK_LIGHT_HIGH,
        PBRICK_LIGHT_LEFT_FRONT,
        PBRICK_LIGHT_RIGHT_FRONT
#ifdef PBRICK_LIGHT_LOW
        ,PBRICK_LIGHT_LOW
#endif
#ifdef PBRICK_LIGHT_LEFT_REAR
        ,PBRICK_LIGHT_LEFT_REAR
#endif
#ifdef PBRICK_LIGHT_RIGHT_REAR
        ,PBRICK_LIGHT_RIGHT_REAR
#endif
#ifdef PBRICK_LIGHT_ACC0
        ,PBRICK_LIGHT_ACC0
#endif
#ifdef PBRICK_LIGHT_ACC1
        ,PBRICK_LIGHT_ACC1
#endif
#ifdef PBRICK_LIGHT_ACC2
        ,PBRICK_LIGHT_ACC2
#endif
    };

    uint8_t count = (uint8_t)(sizeof(lights)/sizeof(lights[0]));
    return pbrick_light_do_option(lights, count, 0x00);
}

void pbrick_light_on()
{
    uint32_t lights[] = {
        PBRICK_LIGHT_HIGH,
        PBRICK_LIGHT_LEFT_FRONT,
        PBRICK_LIGHT_RIGHT_FRONT
#ifdef PBRICK_LIGHT_LOW
        ,PBRICK_LIGHT_LOW
#endif
#ifdef PBRICK_LIGHT_LEFT_REAR
        ,PBRICK_LIGHT_LEFT_REAR
#endif
#ifdef PBRICK_LIGHT_RIGHT_REAR
        ,PBRICK_LIGHT_RIGHT_REAR
#endif
#ifdef PBRICK_LIGHT_ACC0
        ,PBRICK_LIGHT_ACC0
#endif
#ifdef PBRICK_LIGHT_ACC1
        ,PBRICK_LIGHT_ACC1
#endif
#ifdef PBRICK_LIGHT_ACC2
        ,PBRICK_LIGHT_ACC2
#endif
    };

    uint8_t count = (uint8_t)(sizeof(lights)/sizeof(lights[0]));
    return pbrick_light_do_option(lights, count, 0x01);
}

void pbrick_light_low(uint8_t option)
{
#ifdef PBRICK_LIGHT_LOW
    uint32_t lights[] = {
        PBRICK_LIGHT_LOW
    };

    uint8_t count = (uint8_t)(sizeof(lights)/sizeof(lights[0]));
    return pbrick_light_do_option(lights, count, option);
#endif
    return;
}


void pbrick_light_main(uint8_t option)
{
    uint32_t lights[] = {
        PBRICK_LIGHT_LEFT_FRONT,
        PBRICK_LIGHT_RIGHT_FRONT
#ifdef PBRICK_LIGHT_LEFT_REAR
        ,PBRICK_LIGHT_LEFT_REAR
#endif
#ifdef PBRICK_LIGHT_RIGHT_REAR
        ,PBRICK_LIGHT_RIGHT_REAR
#endif
#ifdef PBRICK_LIGHT_LOW
        ,PBRICK_LIGHT_LOW
#endif
    };

    uint8_t count = (uint8_t)(sizeof(lights)/sizeof(lights[0]));
    return pbrick_light_do_option(lights, count, option);
}

void pbrick_light_high(uint8_t option)
{
    uint32_t lights[] = {
        PBRICK_LIGHT_HIGH
    };

    uint8_t count = (uint8_t)(sizeof(lights)/sizeof(lights[0]));
    return pbrick_light_do_option(lights, count, option);
}

void pbrick_light_acc(uint32_t acc, uint8_t option)
{
    uint32_t lights[] = {
        acc
    };
    uint8_t count = (uint8_t)(sizeof(lights)/sizeof(lights[0]));
    return pbrick_light_do_option(lights, count, option);
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
        PBRICK_LIGHT_RIGHT_FRONT
#ifdef PBRICK_LIGHT_LEFT_REAR
        ,PBRICK_LIGHT_LEFT_REAR
#endif
#ifdef PBRICK_LIGHT_RIGHT_REAR
        ,PBRICK_LIGHT_RIGHT_REAR
#endif
#ifdef PBRICK_LIGHT_LOW
        ,PBRICK_LIGHT_LOW
#endif
    };

    uint8_t count = (uint8_t)(sizeof(lights)/sizeof(lights[0]));
    return pbrick_light_blink(lights, count);
}

void pbrick_light_left_blink()
{
    uint32_t lights[] = {
        PBRICK_LIGHT_RIGHT_FRONT
#ifdef PBRICK_LIGHT_RIGHT_REAR
        ,PBRICK_LIGHT_RIGHT_REAR
#endif
    };

    uint8_t count = (uint8_t)(sizeof(lights)/sizeof(lights[0]));
    return pbrick_light_blink(lights, count);
}

void pbrick_light_right_blink()
{
    uint32_t lights[] = {
        PBRICK_LIGHT_LEFT_FRONT
#ifdef PBRICK_LIGHT_LEFT_REAR
        ,PBRICK_LIGHT_LEFT_REAR
#endif
    };

    uint8_t count = (uint8_t)(sizeof(lights)/sizeof(lights[0]));
    return pbrick_light_blink(lights, count);
}

void pbrick_light_blink(uint32_t lights[], uint8_t count)
{
    return pbrick_light_do_option(lights, count, 0x02);
}

void pbrick_light_do_option(uint32_t lights[], uint8_t count, uint8_t option)
{
    switch (option) {
        case 0x00: // Off
            for (uint8_t i = 0; i < count; i++) {
                nrf_gpio_pin_clear(lights[i]);
            }
            break;
        case 0x01: // On
            for (uint8_t i = 0; i < count; i++) {
                nrf_gpio_pin_set(lights[i]);
            }
            break;
        case 0x02: // Blink 3x @500ms
            for (uint8_t i = 0; i < 6; i++) {
                for (uint8_t j = 0; j < count; j++) {
                    nrf_gpio_pin_toggle(lights[j]);
                }
                nrf_delay_ms(500);
            }
            break;
        default:
            break;
    }
}
