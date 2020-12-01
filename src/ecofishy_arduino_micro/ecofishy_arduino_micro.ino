#include <Arduino_JSON.h>
#include "arduino_pin_config.h"
#include "system.h"
#include "ecofishy_state_transition.h"
#include "BP35A1_lib.h"
#include "LED_lib.h"


#define SERIAL0_BAUD 9600
#define SERIAL1_BAUD 9600

long detect_serial_baud_rate(void);
void recv_config(void);

long baud_rate_set[] = {
  115200,
  57600,
  38400,
  28800,
  19200,
  14400,
  9600,
  4800,
  2400,
  1200
};

char g_config[] = "{\"COMPUTE_WAIT_TIME\":1000,\"OP_MODE\":1,\"TEMPERATURE_SENSOR\":2,\"HUMID_SENSOR\":0}";


/*************************************************************************//**
 * @brief initilizem
 * 
 ****************************************************************************/
void setup() {

  // put your setup code here, to run once:
  Serial.begin(SERIAL0_BAUD);

  Serial1.begin(SERIAL1_BAUD);

  // prints title with ending line break
  // setup pins
  pin_init_setup();
  delay(2000);

  
//  led_init();

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
  get_compute_op_mode(&op_mode);

  // host mode
  switch (op_mode) {
  case HOST_MODE:
    host_mode();
    break;

  case SENSOR_MODE:
    // sensor node mode
    sensor_mode();
    break;
  
  default:
    break;
  }

}


long detect_serial_baud_rate(void)
{
    uint8_t baud_rate_index = 0;
    bool rc = false;
    long ret = 115200;

    for (baud_rate_index = 0; baud_rate_index < sizeof(baud_rate_set)/sizeof(long); baud_rate_index++) {
        Serial1.begin(baud_rate_set[baud_rate_index]);
        Serial.println(baud_rate_set[baud_rate_index]);
        delay(1000);
        Serial1.println("SKINFO");
        rc = Serial1.find("OK", 2);
        if (rc == true) {
           ret = baud_rate_set[baud_rate_index];
           break;
        }
        clear_serial_buf();
//        Serial1.end();
    }

    return ret;
}



void recv_config(void)
{
    String str;
    String str_config;

    str = Serial1.readStringUntil("\n");
    Serial.println(str);
    
    Serial.println(str.substring(0,6));
    Serial.println(str.substring(7,8+39));
    Serial.println(str.substring(47,47+39));
    Serial.println(str.substring(87,87+4));
    Serial.println(str.substring(92,92+4));
    Serial.println(str.substring(97,97+16));
    Serial.println(str.substring(114,115));
    Serial.println(str.substring(116,117));
    Serial.println(str.substring(118,122));
    Serial.println(str.substring(123));
    str_config = str.substring(123);
    str_config.toCharArray(g_config, 40);

}