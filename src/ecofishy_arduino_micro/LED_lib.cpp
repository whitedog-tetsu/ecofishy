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

/*************************************************************************//**
 * @brief 
 *        ledのピンは9, 10, 11の値のみ正常動作する
 * 　　　　それ以外は異常の入力値。
 * 
 * 　　　　明るさは0~255までの範囲を正常動作。
 * 　　　　負数は異常とする。
 * 
 * 
 * 
 * 
 * 
 * 
 * @param led_pin 
 * @param brightness
 * @return RESULT_T
 * 
 ****************************************************************************/
RESULT_T led_brightness(int led_pin, int brightness)
{    
    RESULT_T result = NG;

    // pin
    if ((9<=led_pin) && (led_pin <=11)) {
        // brightness
        if ((0<=brightness) && (brightness <=255)) {
            result = OK;
        } else {
            // do nothing
        }
    } else {
        // do nothing
    }
    
    return result;
}


RESULT_T led_blink_msec(int  led_pin, int  pulse_msec)
{
    
}

RESULT_T led_blink_usec(int  led_pin, int  pulse_usec)
{
    
}


void set_led_color(int color)
{
    
}

void get_led_color(int color)
{
    
}



