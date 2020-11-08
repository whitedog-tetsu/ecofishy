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

#ifndef Arduino_h
  #define PIN_A0 0
  #define PIN_A1 1
  #define PIN_A2 2
  #define PIN_A3 3
  #define PIN_A4 4
  #define PIN_A5 5
  #define A0 PIN_A0
  #define A1 PIN_A1
  #define A2 PIN_A2
  #define A3 PIN_A3
  #define A4 PIN_A4
  #define A5 PIN_A5
#endif // Arduino_h
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
