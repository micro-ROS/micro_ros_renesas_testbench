
#ifndef MICROROS_LED__H
#define MICROROS_LED__H

#include "hal_data.h"

#define sleep_ms(X) R_BSP_SoftwareDelay(X, BSP_DELAY_UNITS_MILLISECONDS)

extern bsp_leds_t g_bsp_leds;

typedef enum led_color_t {
    LED_BLUE = 0,
    LED_GREEN = 1,
    LED_RED = 2,
} led_color_t;

static inline void set_led_status(led_color_t led, bool status);

static inline void set_led_status(led_color_t led, bool status)
{
    R_BSP_PinAccessEnable();
    R_BSP_PinWrite(
        (bsp_io_port_pin_t) g_bsp_leds.p_leds[led],
        (status) ? BSP_IO_LEVEL_HIGH : BSP_IO_LEVEL_LOW);
}

#endif  // MICROROS_LED__H
