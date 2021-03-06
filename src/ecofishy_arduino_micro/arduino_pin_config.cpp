/*************************************************************************//**
 * @file arduino_pin_config.c
 * @author typeR
 * @brief 
 * @version 0.1
 * @date 2020-01-19
 * 
 * @copyright Copyright (c) 2020
 * 
 ****************************************************************************/
#include "arduino_pin_config.h"
#include "LED_lib.h"
#ifndef UNIT_TEST
  #include <Arduino.h>
  #include <pins_arduino.h>
#endif // UNIT_TEST

static const ARDUINO_PIN_T s_init_pin_conf[] = {
    //          pin,             io,            logic  
    {(uint8_t)PIN_A0,           (uint8_t)INPUT,        (uint8_t)NULL},  // AT103-11 
    {(uint8_t)PIN_A1,           (uint8_t)INPUT_PULLUP, (uint8_t)NULL},  // Reserved
    {(uint8_t)PIN_A2,           (uint8_t)INPUT_PULLUP, (uint8_t)NULL},  // Reserved
    {(uint8_t)PIN_A3,           (uint8_t)INPUT_PULLUP, (uint8_t)NULL},  // Reserved
    {(uint8_t)PIN_A4,           (uint8_t)INPUT_PULLUP, (uint8_t)NULL},  // other sensors 
    {(uint8_t)PIN_A5,           (uint8_t)INPUT_PULLUP, (uint8_t)NULL},  // other sensors
    {(uint8_t)PIN_UART_TX,      (uint8_t)INPUT_PULLUP, (uint8_t)NULL},  // TX of BP35A1 
    {(uint8_t)PIN_UART_RX,      (uint8_t)INPUT_PULLUP, (uint8_t)NULL},  // RX of BP35A1
    {(uint8_t)PIN_BP35A1_WKUP,  (uint8_t)OUTPUT,       (uint8_t)HIGH},  // BP35A1 WKUP
    {(uint8_t)PIN_BP35A1_RESET, (uint8_t)INPUT_PULLUP, (uint8_t)NULL},  // BP35A1 RESET
    {(uint8_t)PIN_LED_RED,      (uint8_t)OUTPUT,       (uint8_t)MIN_LED_BRIGHTNESS},  // LED R
    {(uint8_t)PIN_LED_BLU,      (uint8_t)OUTPUT,       (uint8_t)MIN_LED_BRIGHTNESS},  // LED G
    {(uint8_t)PIN_LED_GRN,      (uint8_t)OUTPUT,       (uint8_t)MIN_LED_BRIGHTNESS},  // LED B
    {(uint8_t)PIN_SPI_MISO,     (uint8_t)INPUT_PULLUP, (uint8_t)NULL},  // MISO
    {(uint8_t)PIN_SPI_SCLK,     (uint8_t)INPUT_PULLUP, (uint8_t)NULL},  // SCLK
    {(uint8_t)PIN_SPI_MOSI,     (uint8_t)INPUT_PULLUP, (uint8_t)NULL},  // MOSI
    {(uint8_t)PIN_SPI_SS,       (uint8_t)INPUT_PULLUP, (uint8_t)NULL},  // SS
    {(uint8_t)NULL,             (uint8_t)NULL,         (uint8_t)NULL}
};

/*************************************************************************//**
 * @brief 
 * 
 ****************************************************************************/
void pin_init_setup(void)
{
    uint8_t index = (uint8_t)0;
    
    for (index = (uint8_t)0; index < (uint8_t)(sizeof(s_init_pin_conf)/sizeof(ARDUINO_PIN_T)); index++) {   
        switch (s_init_pin_conf[index].io) {
        case INPUT:
            digitalWrite(s_init_pin_conf[index].pin, s_init_pin_conf[index].logic);
            break;

        case OUTPUT: 
            digitalWrite(s_init_pin_conf[index].pin, s_init_pin_conf[index].logic);
            break;

        case INPUT_PULLUP:
            break;

        default:
            pinMode(s_init_pin_conf[index].pin, s_init_pin_conf[index].io);
            break;
        }

    }
}
