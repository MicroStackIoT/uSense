#ifndef _LED_H_
#define _LED_H_

#include "driver/gpio.h"
#include "led_strip.h"

#define LED_GPIO    18U
#define RESOLUTION  10000000U
#define LED_COUNT   1U

void led_init(void);
void led_set_color_red(void);
void led_set_color_green(void);
void led_set_color_blue(void);
void led_set_color_yellow(void);
void led_set_color_magenta(void);
void led_set_color_cyan(void);
void led_set_color_white(void);

#endif

