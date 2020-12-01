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
       analogWrite(led_pin, MAX_LED_BRIGHTNESS);
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
 *        ledのピンは9, 10, 11の値のみ正常動作す�?
 * 　　　　それ以外�?�異常の入力値�?
 * 
 * 　　　　明るさ�?�0~255までの�?囲を正常動作�?
 * 　　　　�?数は異常とする�?
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
    RESULT_T rc = NG;

    // pin
    rc = judge_led_pin(led_pin, PIN_LED_BLU, PIN_LED_RED);
    if (rc == OK) {
        // brightness
        if ((MIN_LED_PWM <= brightness) && (brightness <= MAX_LED_PWM)) {
            analogWrite(led_pin, brightness);
            result = OK;
        } else {
            // do nothing
        }
    } else {
        // do nothing
    }
    
    return result;
}

/*************************************************************************//**
 * @brief 
 * 
 * @param led_pin 
 * @param lower_range 
 * @param upper_range
 * @return RESULT_T 
 ****************************************************************************/
RESULT_T judge_led_pin(int led_pin, int lower_range, int upper_range)
{
    RESULT_T result = NG;

    if ((lower_range <= led_pin) && (led_pin <= upper_range)) {
        result = OK;
    } else {
        // do nothing
    }
    return result;
}

/*************************************************************************//**
 * @brief 
 * 
 *           ON     OFF
 *           pulse_time[msec]
 *          ______     ______
 *        __|     |____|     |___...
 *                      
 *     pulse_time = [10:1000]
 *     repeat_count = [1:10]
 * 
 *     intで扱える数の大きさは処理系による
 *     ex.
 *     8bit  255 
 *     16bit 65535
 *     32bit 
 *     64bit 
 * 
 * @param led_pin 
 * @param pulse_msec 
 * @return RESULT_T 
 ****************************************************************************/
RESULT_T led_blink_msec(int  led_pin, int  pulse_msec, int repeat_count)
{
    RESULT_T result = NG;
    // pin
    if ((PIN_LED_BLU <= led_pin) && (led_pin <= PIN_LED_RED)) {
        // brightness
        if ((MIN_LED_PWM <= brightness) && (brightness <= MAX_LED_PWM)) {
            analogWrite(led_pin, brightness);
            result = OK;
        } else {
            // do nothing
        }
    } else {
        // do nothing
    }

    return result;
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



