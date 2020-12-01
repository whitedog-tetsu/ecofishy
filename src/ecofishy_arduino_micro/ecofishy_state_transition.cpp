/*************************************************************************//**
 * @file ecofishy_state_transition.cpp
 * @author typeR
 * @brief 
 * @version 0.1
 * @date 2020-02-09
 * 
 * @copyright Copyright (c) 2020
 * 
 ****************************************************************************/

#ifndef UNIT_TEST
  #include <Arduino.h>
#else
  #include "stub_arduino.h"
  #include "stub_WString.h"
  #include <string.h>
  #include <iostream>
  #include <string>
  #include <stdio.h>
#endif

#include "ecofishy_state_transition.h"
#include "AT103_11.h"
#include "system.h"
#include <stdint.h>
#include <math.h>
#include "BP35A1_lib.h"
#include "arduino_pin_config.h"
#include "LED_lib.h"

void init_state(OP_STATE_T state)
{
    RESULT_T rc = NG;
    char readByte[256]={'\0'};
    char buf[64] = {'\0'};
    char ipv6_addr[IPV6_ADDR_LEN] = {'\0'};
    uint8_t bufIndex      = (uint8_t)0;
    uint8_t readByteIndex = (uint8_t)0;
    uint8_t readByteSize  = (uint8_t)0;
    uint8_t newline_count = (uint8_t)0;
    uint8_t retry         = (uint8_t)0;

    // set last state
    set_last_state(state);
      
    // clear serial buffer
    clear_serial_buf();
    
    // reset BP35A1
    BP35A1_reset(readByte, &readByteSize);
    
    // write serial monitor
    for (readByteIndex = 0; readByteIndex < (readByteSize+1); readByteIndex++) {
        Serial.write(readByte[readByteIndex]);
    }

    delay(WAIT_STARTUP_BP35A1);  // wait for start up BP35A1

    // initialize destination node information
    init_dst_node_info();

    clear_serial_buf();

    // search destination address
    rc = search_dest_node();
    while(rc == NG) {
        // reset BP35A1
        BP35A1_reset(readByte, &readByteSize);
        clear_serial_buf();
        Serial.println("Connection failed");
        rc = search_dest_node();
    }
    Serial.println("Connection succeeded");


    clear_serial_buf();


    memset(buf, '\0', sizeof(buf));
    get_dst_node_channel(buf);
    for (int i = 0; i < CHANNEL_LEN; i++){
        Serial.print(buf[i]);
    }
    Serial.println();

    memset(buf, '\0', sizeof(buf));
    get_dst_node_channel_page(buf);
    for (int i = 0; i < CHANNEL_PAGE_LEN; i++){
        Serial.print(buf[i]);
    }
    Serial.println();

    memset(buf, '\0', sizeof(buf));
    get_dst_node_lqi(buf);
    for (int i = 0; i < LQI_LEN; i++){
        Serial.print(buf[i]);
    }
    Serial.println();

    memset(buf, '\0', sizeof(buf));
    get_dst_node_pair_id(buf);
    for (int i = 0; i < PAIR_ID_LEN; i++){
        Serial.print(buf[i]);
    }
    Serial.println();

    memset(buf, '\0', sizeof(buf));
    get_dst_node_side(buf);
    for (int i = 0; i < SIDE_LEN; i++){
        Serial.print(buf[i]);
    }
    Serial.println();

    memset(buf, '\0', sizeof(buf));
    get_dst_node_pan_id(buf);
    for (int i = 0; i < PAN_ID_LEN; i++){
        Serial.print(buf[i]);
    }
    Serial.println();

    // check destination MAC address
    memset(buf, '\0', sizeof(buf));
    get_dst_node_mac_addr(buf);
    for (int i = 0; i < MAC_ADDR_LEN; i++){
        Serial.print(buf[i]);
    }
    Serial.println();

    // convert MAC address to IPv6 address
    convert_mac_ipv6(buf, ipv6_addr);

    // set distnation information    
    set_dst_node_ipv6_addr(ipv6_addr);

    set_src_node_handle(BP35A1_UDP_PORT_HNDL_ECHONET_LITE);
    
    set_dst_node_port(BP35A1_UDP_PORT_ECHONET_LITE);
    
    set_dst_node_security(BP35A1_SECURITY_INACTIVE);
    

    //send "READY"
    send_ready();
    clear_serial_buf();
    
    for (retry = 0; retry < MAX_CONNECTION_RETRY; retry++) {
        // wait for "ACK"
        rc = wait_char("ACK", WAIT_TIME_INIT_ACK+(retry*WAIT_TIME_ACK));
        if (rc == OK) {
            // set_err_code();
            break;
        } else {
            send_char("FAIL");
            // set_err_code();
            //send "READY"
            send_ready();
        }
    } 

}


/*************************************************************************//**
 * @brief 
 * 
 * @param state 
 ****************************************************************************/
void compute_init_state(OP_STATE_T state)
{
    RESULT_T rc = OK;
    RESULT_T result = OK;


    // setup pin assign
    
    // save the last state
    set_last_state(state);
    

    // establish Wi-SUN connection
//    rc = wakeup_bp35a1();
//    if (rc != OK) {
//        // write_err_code();
//    }
//
    // inquire sensor node configuration
    rc = inquire_sensor_node_config();
    if (rc != OK) {
        // write_err_code();
    }

    // update sensor node configuration
    rc = update_sensor_node_config();
    if (rc != OK) {
        // write_err_code();
    }

    set_next_state(COMPUTE_MEASURE_STATE);

}

/*************************************************************************//**
 * @brief Wait for the desired character within the time 
 *        
 * 
 * @param buf character
 * @param time_msec 
 * @return RESULT_T 
 ****************************************************************************/
RESULT_T wait_char(char* buf, uint16_t time_msec)
{
    RESULT_T ret = NG;
    boolean  rc  = false;

    Serial1.setTimeout(time_msec);
    rc = Serial1.find(buf);
    if (rc == true) {
        ret = OK;
    } else {
        ret = NG;
    }

    return ret;
}

/*************************************************************************//**
 * @brief 
 * 
 * @param buf 
 ****************************************************************************/
void send_char(const char* buf)
{
    PACKET_T packet = {{'\0'}, (uint8_t)0};
    char payload[PAYLOAD_LEN] = {'\0'};

    strcat(payload, buf);

    // make payload data
    make_send_packet(payload, &packet);

    // send data
    send_packet(packet.data);

}

/*************************************************************************//**
 * @brief 
 * 
 ****************************************************************************/
void send_ready(void)
{
    send_char("READY");
}

/*************************************************************************//**
 * @brief 
 * 
 * @param state 
 ****************************************************************************/
void compute_measure_state(const OP_STATE_T state)
{
    MEASURE_TEMPER_T data = {0.0, 0.0};
    PACKET_T packet = {{'\0'}, (uint8_t)0};
    char temper[6] = {'\0'};
    char payload[PAYLOAD_LEN] = {'\0'};
    uint8_t seq_num = (uint8_t)0;
    
    // save the last state
    set_last_state(state);

    // measure temperature
    compute_measure_temperature(&data);
    
    // collect system status
    seq_num = get_sequence_num();

    // data alignment
    sprintf(payload, "%X", seq_num);
    strcat(payload, DELIM_SPACE);
    dtostrf(data.temper_degc1, 5, 2, temper);
    strcat(payload, temper);
    memset(temper, '\0', sizeof(temper));
    dtostrf(data.temper_degc2, 5, 2, temper);
    strcat(payload, DELIM_SPACE);
    strcat(payload, temper);

    // make payload data
    make_send_packet(payload, &packet);

    // send data
    send_packet(packet.data);
    
    inc_sequence_num((uint8_t)1);
   
    // next state
    set_next_state(COMPUTE_WAIT_STATE);
    
}

/*************************************************************************//**
 * @brief 
 * 
 * @param state 
 ****************************************************************************/
void compute_measure_temperature(MEASURE_TEMPER_T* data)
{
    DATA_TEMPERATURE16_T data_temper[MAX_DATA_TEMPER_SIZE] = {0,};  // read data buffer
    DATA_TEMPERATURE32_T sum_temper = {0,0,0};  // sum of temperature
    DATA_TEMPERATURE16_T ave_temper = {0,0,0};  // averaged temperature 
    DATA_TEMPERATURE32F_T degc      = {0.0, 0.0, 0.0};  // degree celcius
    uint8_t  index      = (uint8_t)0;   // loop variable
    
    
    // sampling
    for (index = (uint8_t)0; index < (uint8_t)MAX_DATA_TEMPER_SIZE; index++) {
        data_temper[index].src1 = analogRead(A0);
        data_temper[index].src2 = analogRead(A1);
    } 

    // calculate

    // sum
    for (index = (uint8_t)0; index < (uint8_t)SUM_DATA_TEMPER_SIZE; index++) {
        sum_temper.src1 += (int32_t)data_temper[index].src1;
        sum_temper.src2 += (int32_t)data_temper[index].src2;
    }

    // divide
    round_temper_data(&sum_temper.src1, (int32_t)ROUND_DATA_TEMPER_DIGIT);
    round_temper_data(&sum_temper.src2, (int32_t)ROUND_DATA_TEMPER_DIGIT);

    ave_temper.src1 = (uint16_t)(sum_temper.src1 / (uint32_t)AVERAGE_DATA_TEMPER_SIZE);
    ave_temper.src2 = (uint16_t)(sum_temper.src2 / (uint32_t)AVERAGE_DATA_TEMPER_SIZE);

    // convert
    convert_analog2degc(&ave_temper.src1, &data->temper_degc1);
    convert_analog2degc(&ave_temper.src2, &data->temper_degc2);

    // fixed point value
//    data->temper_degc1 = (int16_t)(degc.src1 * (int16_t)100);
//    data->temper_degc2 = (int16_t)(degc.src2 * (int16_t)100);
}

/*************************************************************************//**
 * @brief 
 * 
 * @return RESULT_T 
 ****************************************************************************/
RESULT_T start_compute_measure_state(void)
{
    RESULT_T rc = OK;
    RESULT_T result = OK;

    rc = wakeup_bp35a1();
    if (rc != OK) {
        // write_err_code();
    }

    // inquire sensor node configuration
    rc = inquire_sensor_node_config();
    if (rc != OK) {
        // write_err_code();
    }

    // update sensor node configuration
    rc = update_sensor_node_config();
    if (rc != OK) {
        // write_err_code();
    }

    return result;

}

/*************************************************************************//**
 * @brief 
 * 
 * @return RESULT_T 
 ****************************************************************************/
RESULT_T end_compute_measure_state(void)
{
    RESULT_T result = OK;

    return result;
}



/*************************************************************************//**
 * @brief 
 * 
 * @param data 
 * @param digit 
 * @return uint16_t 
 ****************************************************************************/
void round_temper_data(int32_t* data, int32_t digit)
{
    if ((int32_t)0 <= *data) {
        *data += digit;
    } else {
        *data -= digit;
    }

}

/*************************************************************************//**
 * @brief 
 * 
 * @param readByte 
 * @return RESULT_T 
 ****************************************************************************/
RESULT_T search_dest_node(void)
{
    RESULT_T ret = OK;
    String str_skscan       = {"\0"};  // SKSCAN  
    String str_ok           = {"\0"};  // OK
    String str_event_20     = {"\0"};  // EVENT 20
    String str_epandesc     = {"\0"};  // EPANDESC
    String str_channel      = {"\0"};  // CH
    String str_channel_page = {"\0"};  // Channel page
    String str_pan_id       = {"\0"};  // PAN ID
    String str_mac_addr     = {"\0"};  // Addr
    String str_lqi          = {"\0"};  // LQI
    String str_side         = {"\0"};  // Side
    String str_pair_id      = {"\0"};  // Pair ID
    String str_event_22     = {"\0"};  // EVENT 22
    char buf[BUF_SIZE] ={ "\0"};

    clear_serial_buf();
    
    // SKSCAN
    Serial1.print(bp35a1_cmd_set[7].skcmd);
    Serial1.println(" 2 FFFFFFFF 6 0");
    str_skscan       = Serial1.readStringUntil('\n'); // SKSCAN
    str_ok           = Serial1.readStringUntil('\n'); // OK
    str_event_20     = Serial1.readStringUntil('\n'); // EVENT20
    str_epandesc     = Serial1.readStringUntil('\n'); // EPANDESC
    str_channel      = Serial1.readStringUntil('\n'); // CH
    str_channel_page = Serial1.readStringUntil('\n'); // CH page
    str_pan_id       = Serial1.readStringUntil('\n'); // PAN ID
    str_mac_addr     = Serial1.readStringUntil('\n'); // Addr
    str_lqi          = Serial1.readStringUntil('\n'); // LQI
    str_side         = Serial1.readStringUntil('\n'); // Side
    str_pair_id      = Serial1.readStringUntil('\n'); // Pair ID
    Serial1.setTimeout(WAIT_TIME_EVENT22);
    str_event_22 = Serial1.readStringUntil('\n');     // EVENT22
    

    if(str_channel.equals("") == true) return NG;
//    if(str_channel_page.equals("") == false) return NG;
//    if(str_pan_id.equals("") == false) return NG;
//    if(str_mac_addr.equals("") == true) return NG;
//    if(str_lqi.equals("") == false) return NG;
//    if(str_side.equals("") == false) return NG;
//    if(str_pair_id.equals("") == false) return NG;

    // erase white space
    str_channel.trim(); 
    str_channel_page.trim();
    str_pan_id.trim();
    str_mac_addr.trim();
    str_lqi.trim();
    str_side.trim();
    str_pair_id.trim();
    

    // channel
    str_channel.toCharArray(buf, str_channel.length()+1);
    Serial.println(str_channel);
    set_dst_node_channel(&buf[8]);

    // channel page
    memset(buf, '\0', sizeof(buf));
    str_channel_page.toCharArray(buf, str_channel_page.length()+1);
    Serial.println(str_channel_page);
    set_dst_node_channel_page(&buf[13]);

    // PAN ID
    memset(buf, '\0', sizeof(buf));
    str_pan_id.toCharArray(buf, str_pan_id.length()+1);
    Serial.println(str_pan_id);
    set_dst_node_pan_id(&buf[7]);

    // MAC address
    memset(buf, '\0', sizeof(buf));
    str_mac_addr.toCharArray(buf, str_mac_addr.length()+1);
    set_dst_node_mac_addr(&buf[5]);
    
    // LQI
    memset(buf, '\0', sizeof(buf));
    str_lqi.toCharArray(buf, str_lqi.length()+1);
    set_dst_node_lqi(&buf[4]);

    // Side
    memset(buf, '\0', sizeof(buf));
    str_side.toCharArray(buf, str_side.length()+1);
    set_dst_node_side(&buf[5]);
    
    // pair_id
    memset(buf, '\0', sizeof(buf));
    str_pair_id.toCharArray(buf, str_pair_id.length()+1);
    set_dst_node_pair_id(&buf[7]);

    return ret;

}

