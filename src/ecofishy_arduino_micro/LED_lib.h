#ifndef LED_LIB_H
#define LED_LIB_H

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

#include "arduino_pin_config.h"

#define PIN_LED_BLU (9) 
#define PIN_LED_GRN (10) 
#define PIN_LED_RED (11)

#define MAX_LED_PWM (255)
#define MIN_LED_PWM (0)


extern void set_led_stat(ARDUINO_PIN_T* pin_info);
extern void get_led_stat(ARDUINO_PIN_T* pin_info);

extern void led_init(void);

extern void led_all_on(void);
extern void led_all_off(void);

extern void led_on(int led_pin);
extern void led_off(int led_pin);

extern void led_brightness(int led_pin, int brightness);

extern void led_blink_msec(int  led_pin, int  pulse_msec, int init_led_stat);
extern void led_blink_usec(int  led_pin, int  pulse_usec, int init_led_stat);

extern void set_led_color(int color);
extern void get_led_color(int color);


#ifdef __cplusplus
}
#endif // __cplusplus

#endif // LED_LIB_H

