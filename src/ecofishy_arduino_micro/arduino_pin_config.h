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
