#include "led.h"

static led_strip_handle_t led_strip;

void led_init(void)
{
    /* LED strip initialization with the GPIO and pixels number*/
    led_strip_config_t strip_config = {
        .strip_gpio_num = LED_GPIO,
        .max_leds = LED_COUNT,
    };

    led_strip_rmt_config_t rmt_config = {
        .resolution_hz = RESOLUTION,
        .flags.with_dma = false,
    };

    ESP_ERROR_CHECK(led_strip_new_rmt_device(&strip_config, &rmt_config, &led_strip));
    led_strip_clear(led_strip);
}

void led_set_color_red(void)
{
    led_strip_set_pixel(led_strip, 0, 16, 0, 0);
    led_strip_refresh(led_strip);
}

void led_set_color_green(void)
{
    led_strip_set_pixel(led_strip, 0, 0, 16, 0);
    led_strip_refresh(led_strip);
    
}

void led_set_color_blue(void)
{
    led_strip_set_pixel(led_strip, 0, 0, 0, 16);
    led_strip_refresh(led_strip);
    
}

void led_set_color_yellow(void)
{
    led_strip_set_pixel(led_strip, 0, 16, 16, 0);
    led_strip_refresh(led_strip);
}

void led_set_color_magenta(void)
{
    led_strip_set_pixel(led_strip, 0, 16, 0, 16);
    led_strip_refresh(led_strip);
}

void led_set_color_cyan(void)
{
    led_strip_set_pixel(led_strip, 0, 0, 16, 16);
    led_strip_refresh(led_strip);
}

void led_set_color_white(void)
{
    led_strip_set_pixel(led_strip, 0, 16, 16, 16);
    led_strip_refresh(led_strip);
}