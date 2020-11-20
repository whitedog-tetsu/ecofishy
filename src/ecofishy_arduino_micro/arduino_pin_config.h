#ifndef ARDUINO_PIN_CONFIG_H
#define ARDUINO_PIN_CONFIG_H

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

//#include <stdint.h>

#ifndef LED_LIB_H
  #define PIN_LED_BLU (9) 
  #define PIN_LED_GRN (10) 
  #define PIN_LED_RED (11)
#endif // LED_LIB_H

#if !defined(Arduino_h) && defined(UNIT_TEST)
  #define PIN_A0 14
  #define PIN_A1 15
  #define PIN_A2 16
  #define PIN_A3 17
  #define PIN_A4 18
  #define PIN_A5 19
  #define A0 PIN_A0
  #define A1 PIN_A1
  #define A2 PIN_A2
  #define A3 PIN_A3
  #define A4 PIN_A4
  #define A5 PIN_A5
#endif // Arduino_h

#define PIN_UART_TX 0
#define PIN_UART_RX 1
#define PIN_BP35A1_WKUP  4
#define PIN_BP35A1_RESET 5
#define PIN_SPI_MISO 14
#define PIN_SPI_SCLK 15
#define PIN_SPI_MOSI 16
#define PIN_SPI_SS   17


typedef struct arduino_pin_t {
    int pin;
    int io;
    int logic;
} ARDUINO_PIN_T;


extern void pin_init_setup(void);


#ifdef __cplusplus
}
#endif // __cplusplus

#endif // ARDUINO_PIN_CONFIG_H
