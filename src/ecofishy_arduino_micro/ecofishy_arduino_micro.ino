#include "arduino_pin_config.h"
#include "system.h"
#include "ecofishy_state_transition.h"
#include "BP35A1_lib.h"
#include "LED_lib.h"

#define SERIAL0_BAUD 9600
#define SERIAL1_BAUD 9600

/*************************************************************************//**
 * @brief initilizem
 * 
 ****************************************************************************/
void setup() {

  // put your setup code here, to run once:
  Serial.begin(SERIAL0_BAUD);

  Serial1.begin(SERIAL1_BAUD);
  while (!Serial1) {
    ; // wait for serial port to connect. Needed for native USB port only
  }


  // prints title with ending line break
  // setup pins
  pin_init_setup();
  delay(1000);  

  led_init();
  
  init_state(INIT_STATE);

  set_next_state(COMPUTE_INIT_STATE);

}

/*************************************************************************//**
 * @brief Main loop 
 * 
 ****************************************************************************/
void loop() {
  // put your main code here, to run repeatedly:
  OP_MODE_T op_mode = DEFAULT_MODE;

  // get operate mode
  op_mode = SENSOR_MODE;

  // host mode
  switch (op_mode) {
  case HOST_MODE:
    break;

  case SENSOR_MODE:
    // sensor node mode
    sensor_mode();

    break;
  
  default:
    break;
  }

}

