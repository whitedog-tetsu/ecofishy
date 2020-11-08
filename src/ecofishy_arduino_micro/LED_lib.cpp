#include "LED_lib.h"
#include "arduino_pin_config.h"

#ifndef UNIT_TEST
  #include <Arduino.h>
  #include <pins_arduino.h>
#else
  #include "stub_arduino.h"
#endif // UNIT_TEST


void set_led_stat(ARDUINO_PIN_T* pin_info)
{
    analogWrite(pin_info->pin, pin_info->logic);
}

void get_led_stat(ARDUINO_PIN_T* pin_info)
{
    pin_info->logic = analogRead(pin_info->pin);
}


void led_init(void)
{
    pinMode(PIN_LED_RED, OUTPUT);
    pinMode(PIN_LED_BLU, OUTPUT);
    pinMode(PIN_LED_GRN, OUTPUT);

    led_all_off();
}


void led_all_on(void)
{
    led_on(PIN_LED_RED);
    led_on(PIN_LED_BLU);
    led_on(PIN_LED_GRN);
}

void led_all_off(void)
{
    led_off(PIN_LED_RED);
    led_off(PIN_LED_BLU);
    led_off(PIN_LED_GRN);
}


RESULT_T led_on(uint8_t led_pin)
{
    RESULT_T ret = NG;

    if ((PIN_LED_BLU <= led_pin) && (led_pin <= PIN_LED_RED)) {
       analogWrite(led_pin, MIN_LED_PWM);
       ret = OK;
    } else {
        // do nothing
    }

    return ret;
}

RESULT_T led_off(int led_pin)
{
    RESULT_T ret = NG;

    if ((PIN_LED_BLU <= led_pin) && (led_pin <= PIN_LED_RED)) {
       analogWrite(led_pin, MAX_LED_PWM);
       ret = OK;
    } else {
        // do nothing
    }

    return ret;
}


void led_brightness(int led_pin, int brightness)
{
    
}


void led_blink_msec(int  led_pin, int  pulse_msec, int init_led_stat)
{
    
}

void led_blink_usec(int  led_pin, int  pulse_usec, int init_led_stat)
{
    
}


void set_led_color(int color)
{
    
}

void get_led_color(int color)
{
    
}



