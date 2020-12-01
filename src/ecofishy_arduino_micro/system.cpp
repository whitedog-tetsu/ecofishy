#include "system.h"
#include "ecofishy_state_transition.h"
#include "LED_lib.h"

#ifndef UNIT_TEST
  #include <Arduino_JSON.h>
  #include <avr/wdt.h>
  #include <Arduino.h>
#else
  #include "stub_arduino.h"
#endif // UNIT_TEST

static OP_STATE_T s_op_state = OP_STATE_DEFAULT; 
static uint16_t   s_err_code = (uint16_t)0x00;
static uint8_t    s_seq_num  = (uint8_t)0;
static NODE_CONFIG_T s_node_config = {
    {0,0,0,0,0},
    DEFAULT_COMP_WAIT_TIME,
    0,
    SENSOR_MODE,
    0
};

void clear_serial_buf(void)
{
    while(0 <= Serial.read());
    while(0 <= Serial1.read());
}

/*************************************************************************//**
 * @brief 
 * 
 ****************************************************************************/
void sensor_mode(void)
{

  OP_STATE_T op_state = OP_STATE_DEFAULT;
  uint16_t   wait_time = 0;
  RESULT_T   rc = NG;

  // get next state
  op_state = get_next_state();

  switch (op_state) {

  case COMPUTE_INIT_STATE:
      led_on(PIN_LED_RED);
      compute_init_state(op_state);
      led_off(PIN_LED_RED);
      break;

  case COMPUTE_MEASURE_STATE:
      led_on(PIN_LED_BLU);
      compute_measure_state(op_state);
      led_off(PIN_LED_BLU);
      break;

  case COMPUTE_WAIT_STATE:
      led_on(PIN_LED_GRN);
      set_next_state(COMPUTE_MEASURE_STATE);
      get_compute_wait_time(&wait_time);
      rc = sleep_bp35a1();
      if (rc == OK) {
          Serial.println("Sleeping");
      }
      delay(wait_time);
      wakeup_bp35a1();
      led_off(PIN_LED_GRN);
      break;

  default:
      break;
  }

}

/*************************************************************************//**
 * @brief 
 * 
 ****************************************************************************/
void host_mode(void)
{
//    while(1){
//        if (0 < Serial1.available()) {
//            Serial.write(Serial1.read());
//        }
//    }
}

/*************************************************************************//**
 * @brief Get the last state object
 * 
 * @return OP_STATE_T 
 ****************************************************************************/
OP_STATE_T get_last_state(void)
{
    return s_op_state;
}

/*************************************************************************//**
 * @brief Set the last state object
 * 
 * @param state 
 ****************************************************************************/
void set_last_state(const OP_STATE_T state)
{
    s_op_state = state;
}

/*************************************************************************//**
 * @brief Get the next state object
 * 
 * @return OP_STATE_T 
 ****************************************************************************/
OP_STATE_T get_next_state(void)
{
    return s_op_state;
}

/*************************************************************************//**
 * @brief Set the next state object
 * 
 * @param state 
 ****************************************************************************/
void set_next_state(const OP_STATE_T state)
{
    s_op_state = state;
}

/*************************************************************************//**
 * @brief Set the up uart object
 * 
 ****************************************************************************/
void system_setup_uart(void)
{

}

/*************************************************************************//**
 * @brief Set the up i2c object
 * 
 ****************************************************************************/
void system_setup_i2c(void)
{
   
}

/*************************************************************************//**
 * @brief 
 * 
 * @param err_bit 
 ****************************************************************************/
void set_err_bit(const uint8_t err_bit)
{
//    bitSet(s_err_code, err_bit);
}

/*************************************************************************//**
 * @brief 
 * 
 * @param err_bit 
 * @return uint8_t 
 ****************************************************************************/
uint8_t get_err_bit(const uint8_t err_bit)
{
//    return bitRead(s_err_code, err_bit);
    return 0;
}

void clear_err_bit(const uint8_t err_bit)
{
//    bitClear(s_err_code, err_bit);
}

void init_err_bit(void)
{
    s_err_code = 0;
}


uint16_t get_err_code(void)
{
    return s_err_code;
}


/*************************************************************************//**
 * @brief 
 * 
 * @return RESULT_T 
 ****************************************************************************/
RESULT_T inquire_sensor_node_config(void)
{
    RESULT_T result = OK;

    // request config
//    send_char("REQCONFIG");
    

    return result;
}


/*************************************************************************//**
 * @brief 
 * 
 * @return RESULT_T 
 ****************************************************************************/
RESULT_T update_sensor_node_config(void)
{
    RESULT_T result = OK;
    char     buf[10] = {'\0'};

    return result;
}

/*************************************************************************//**
 * @brief 
 * 
 * @return RESULT_T 
 ****************************************************************************/
RESULT_T wakeup_bp35a1(void)
{
    RESULT_T result = NG;
    RESULT_T rc = NG;
    
    while(1) {
        pinMode(PIN_BP35A1_WKUP, OUTPUT);
        digitalWrite(PIN_BP35A1_WKUP, LOW);
        delay(10);
        digitalWrite(PIN_BP35A1_WKUP, HIGH);
        rc = check_awaken_bp35a1();
        if (rc != NG) {
            Serial.println("BP35A1 woke up");
            result = OK;
            break;
        }

    }

    return result;
}

RESULT_T sleep_bp35a1(void)
{
    RESULT_T result = OK;
    RESULT_T rc = NG;
    
    digitalWrite(PIN_BP35A1_WKUP, LOW);
    Serial1.println("SKDSLEEP");
    rc = check_awaken_bp35a1();
    if (rc != NG) {
        result = NG;
    }

    return result;

}

/*************************************************************************//**
 * @brief 
 * 
 * @return RESULT_T 
 ****************************************************************************/
RESULT_T check_awaken_bp35a1(void)
{
    RESULT_T result = OK;
    bool rc = false;
    
    Serial1.println("SKINFO");
    rc = Serial1.find("OK", 2);
    if (rc == false) {
        result = NG;
    }

    return result;
}

void inc_sequence_num(uint8_t step)
{
    s_seq_num += step;
}

void dec_sequence_num(uint8_t step)
{
    s_seq_num -= step;
}

uint8_t get_sequence_num(void)
{
    return s_seq_num;
}

void set_sequence_num(const uint8_t seq_num)
{
    s_seq_num = seq_num;
}


void init_sequence_num(void)
{
    set_sequence_num(0);
}

void software_reset(void)
{
    wdt_disable();
    wdt_enable(WDTO_1S);
//    while (1) {}
}

void get_compute_wait_time(uint16_t* wait_time)
{
    *wait_time = s_node_config.wait_time;
}

void set_compute_wait_time(const uint16_t wait_time)
{
    s_node_config.wait_time = wait_time;
}

void get_compute_op_mode(OP_MODE_T* op_mode)
{
    *op_mode = s_node_config.op_mode;    
}

void set_compute_op_mode(const OP_MODE_T op_mode)
{
    s_node_config.op_mode = op_mode;
}


RESULT_T set_sensor_node_config(const NODE_CONFIG_T* data)
{
    RESULT_T result = NG;

    set_compute_wait_time(data->wait_time);
    set_compute_op_mode(data->op_mode);

    return result;
}

RESULT_T get_sensor_node_config(NODE_CONFIG_T* data)
{
    RESULT_T result = NG;

    get_compute_wait_time(&data->wait_time);

    return result;

}


void ecofishy_config_parse(const char* config)
{
  JSONVar ecofishy_object = JSON.parse(config);


  // JSON.typeof(jsonVar) can be used to get the type of the var
  if (JSON.typeof(ecofishy_object) == "undefined") {
    Serial.println("Parsing input failed!");
    return;
  }

  Serial.print("JSON.typeof(ecofishy_object) = ");
  Serial.println(JSON.typeof(ecofishy_object)); // prints: object

  // myObject.hasOwnProperty(key) checks if the object contains an entry for key
  if (ecofishy_object.hasOwnProperty(STR_COMPUTE_WAIT_TIME)) {
    Serial.print("ecofishy_object[\"COMPUTE_WAIT_TIME\"] = ");

    Serial.println((int) ecofishy_object[STR_COMPUTE_WAIT_TIME]);
  }

  if (ecofishy_object.hasOwnProperty(STR_OP_MODE)) {
    Serial.print("ecofishy_object[\"OP_MODE\"] = ");

    Serial.println((int) ecofishy_object[STR_OP_MODE]);
  }


  // JSON vars can be printed using print or println
  Serial.print("ecofishy_object = ");
  Serial.println(ecofishy_object);

  Serial.println();

}

#if 0
void ecofishy_config_parse_str(const String& config)
{

  JSONVar ecofishy_object = JSON.parse(config);


  // JSON.typeof(jsonVar) can be used to get the type of the var
  if (JSON.typeof(ecofishy_object) == "undefined") {
    Serial.println("Parsing input failed!");
    return;
  }

  Serial.print("JSON.typeof(ecofishy_object) = ");
  Serial.println(JSON.typeof(ecofishy_object)); // prints: object

  // myObject.hasOwnProperty(key) checks if the object contains an entry for key
  if (ecofishy_object.hasOwnProperty(STR_COMPUTE_WAIT_TIME)) {
    Serial.print("ecofishy_object[\"COMPUTE_WAIT_TIME\"] = ");

    Serial.println((int) ecofishy_object[STR_COMPUTE_WAIT_TIME]);
  }

  if (ecofishy_object.hasOwnProperty(STR_OP_MODE)) {
    Serial.print("ecofishy_object[\"OP_MODE\"] = ");

    Serial.println((int) ecofishy_object[STR_OP_MODE]);
  }


  // JSON vars can be printed using print or println
  Serial.print("ecofishy_object = ");
  Serial.println(ecofishy_object);

  Serial.println();
    
}
#endif
// get_data
// set_data
// interrupt
