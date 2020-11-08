#include "system.h"
#include "ecofishy_state_transition.h"
#include "LED_lib.h"

#ifndef UNIT_TEST
  #include <Arduino_JSON.h>
  #include <avr/wdt.h>
  #include <Arduino.h>
#endif // UNIT_TEST

static OP_STATE_T s_op_state = OP_STATE_DEFAULT; 
static uint16_t   s_err_code = (uint16_t)0x00;
static uint8_t    s_seq_num  = (uint8_t)0;
static NODE_CONFIG_T s_node_config;
static uint16_t s_compute_wait_time = (uint16_t)DEFAULT_COMP_WAIT_TIME;

void clear_serial_buf(void)
{
//    while(Serial.read() >= 0);
//    while(Serial1.read() >= 0);

}

/*************************************************************************//**
 * @brief 
 * 
 ****************************************************************************/
void sensor_mode(void)
{

  OP_STATE_T op_state = OP_STATE_DEFAULT;
  uint16_t   wait_time = 0;

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
      wait_time = get_compute_wait_time();
      delay(wait_time);
//      software_reset();
      set_next_state(COMPUTE_MEASURE_STATE);
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
    uint8_t readByteIndex = (uint8_t)0;
    uint8_t newline_count = (uint8_t)0;
//    boolean  rc = false;
//    String   str;
    char     buf[10] = {'\0'};
//    JSONVar  myArray;

//    Serial1.setTimeout(3000);
//    str = Serial1.readStringUntil("\n");
//    Serial.println(str);
//    myArray = JSON.parse(str);

    return result;
}

/*************************************************************************//**
 * @brief 
 * 
 * @return RESULT_T 
 ****************************************************************************/
RESULT_T wakeup_bp35a1(void)
{
    RESULT_T result = OK;
    RESULT_T rc = OK;
    // pinMode(BP35A1_WAKEUP_PIN, LOW);
    // pinMode(BP35A1_WAKEUP_PIN, HIGH);
    // pinMode(BP35A1_WAKEUP_PIN, HIGH);

//    rc = check_awaken_bp35a1();
//    if (rc != OK) {
//        result = NG;
//    }

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
    RESULT_T rc = OK;
    
//    Serial1.println("SKINFO");
//    Serial.println("SKINFO");
//    rc = wait_char("OK", 1000);
    if (rc != OK) {
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
//    wdt_disable();
//    wdt_enable(WDTO_1S);
    while (1) {}
}

uint16_t get_compute_wait_time(void)
{
    return s_compute_wait_time;
}

void set_compute_wait_time(uint16_t wait_time)
{
    s_compute_wait_time = wait_time;
}

// get_data
// set_data
// interrupt
