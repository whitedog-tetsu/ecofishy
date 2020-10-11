/*************************************************************************//**
 * @file BP35A1.c
 * @author typeR
 * @brief 
 * @version 0.1
 * @date 2020-01-19
 * 
 * @copyright Copyright (c) 2020
 * 
 ****************************************************************************/

#include <Arduino.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "BP35A1_lib.h"
#include "system.h"

static BP35A1_NODE_T s_dst_node;
static BP35A1_NODE_T s_src_node;

BP35A1_CMD_T bp35a1_cmd_set[8] = {
    // skcmd,             param0, param1, param2, param3, param4, param5, param6, param7, recv_line     
    {BP35A1_CMD_SKINFO,   NULL,   NULL,   NULL,   NULL,   NULL,   NULL,   NULL,   NULL,   BP35A1_CMD_SKINFO_RECV_LINE},   // 
    {BP35A1_CMD_SKVER,    NULL,   NULL,   NULL,   NULL,   NULL,   NULL,   NULL,   NULL,   BP35A1_CMD_SKVER_RECV_LINE},    // 
    {BP35A1_CMD_SKPING,   NULL,   NULL,   NULL,   NULL,   NULL,   NULL,   NULL,   NULL,   BP35A1_CMD_SKPING_RECV_LINE},   // 
    {BP35A1_CMD_SKSENDTO, NULL,   NULL,   NULL,   NULL,   NULL,   NULL,   NULL,   NULL,   BP35A1_CMD_SKSENDTO_RECV_LINE}, // 
    {BP35A1_CMD_SKRESET,  NULL,   NULL,   NULL,   NULL,   NULL,   NULL,   NULL,   NULL,   BP35A1_CMD_SKRESET_RECV_LINE},  // 
    {BP35A1_CMD_SKDSLEEP, NULL,   NULL,   NULL,   NULL,   NULL,   NULL,   NULL,   NULL,   BP35A1_CMD_SKDSLEEP_RECV_LINE}, // 
    {BP35A1_CMD_SKSTART,  NULL,   NULL,   NULL,   NULL,   NULL,   NULL,   NULL,   NULL,   BP35A1_CMD_SKSTART_RECV_LINE},  // 
    {BP35A1_CMD_SKSCAN,   NULL,   NULL,   NULL,   NULL,   NULL,   NULL,   NULL,   NULL,   BP35A1_CMD_SKSCAN_RECV_LINE}    // 
};


/*************************************************************************//**
 * @brief 
 * 
 * @param mac_addr 
 * @param ipv6_addr 
 ****************************************************************************/
void convert_mac_ipv6(const char* mac_addr, char* ipv6_addr)
{
    char readByte[65] = {'0'};
    uint8_t readByteIndex = (uint8_t)0;
    uint8_t newline_count = (uint8_t)0;
    String str_skll64 = {"\0"};
    String str_ipv6 = {"\0"};

    clear_serial_buf();

    Serial1.print(BP35A1_CMD_SKLL64);
    Serial1.print(" ");
    Serial1.println(mac_addr);
    str_skll64 = Serial1.readStringUntil('\n'); // SKLL64
    str_ipv6 = Serial1.readStringUntil('\n'); // ipv6
    
//    Serial.println(str0);
//    Serial.println(str1);

    str_ipv6.toCharArray(readByte, str_ipv6.length()+1);

    memcpy(ipv6_addr, readByte, IPV6_ADDR_LEN);

}

/*************************************************************************//**
 * @brief 
 * 
 * @param buf 
 * @param buf_size 
 * @return RESULT_T 
 ****************************************************************************/
RESULT_T BP35A1_reset(char* buf, uint8_t* buf_size)
{
    BP35A1_cmd_send(&bp35a1_cmd_set[4], 5000, buf, buf_size);
}

/*************************************************************************//**
 * @brief 
 * 
 * @param buf 
 * @param buf_size 
 * @return RESULT_T 
 ****************************************************************************/
RESULT_T BP35A1_scan_dst_device(char* buf, uint8_t* buf_size)
{
    Serial1.println(BP35A1_CMD_SKRESET);
    Serial1.findUntil("OK", "\n");

//    BP35A1_cmd_send(&bp35a1_cmd_set[7], 5000, buf, buf_size);
}

RESULT_T BP35A1_check_fw_version(char* buf, uint8_t* buf_size)
{
    BP35A1_cmd_send(&bp35a1_cmd_set[1], 5000, buf, buf_size);
}

/*************************************************************************//**
 * @brief 
 * 
 * @param cmd 
 * @param timeout_msec 
 * @param readbuf 
 * @param readbuf_size 
 * @return RESULT_T 
 ****************************************************************************/
RESULT_T BP35A1_cmd_send(const BP35A1_CMD_T* cmd, const uint32_t timeout_msec, char* readbuf, uint8_t* readbuf_size)
{
    uint8_t newline_count = 0;
    RESULT_T result = NG;
    uint32_t start_time = 0;

    int i;

    clear_serial_buf();

    start_time = millis();

    Serial1.println(cmd->skcmd);
    while((millis() - start_time) <= timeout_msec) {
        if (0<Serial1.available()) {
            readbuf[*readbuf_size] = Serial1.read();
            if (readbuf[*readbuf_size] == BP35A1_CMD_NEWLINE) {
                newline_count++;
                if (newline_count == cmd->recv_line) {
                    result = OK;
                    break;
                }
            }
            (*readbuf_size)++;
        }
    }
    
    return result;
}

void init_dst_node_info(void)
{
    memcpy(&s_dst_node, "\0", sizeof(BP35A1_NODE_T));
}


void get_dst_node_info(BP35A1_NODE_T* dst_node)
{
    memcpy(dst_node, &s_dst_node, sizeof(s_dst_node));
}


void set_dst_node_info(const BP35A1_NODE_T* dst_node)
{
    memcpy(&s_dst_node, dst_node, sizeof(s_dst_node));
}

void set_dst_node_mac_addr(const char* mac_addr)
{
    memcpy(s_dst_node.mac_addr, mac_addr, sizeof(s_dst_node.mac_addr));
}

void get_dst_node_mac_addr(char* mac_addr)
{
    memcpy(mac_addr, s_dst_node.mac_addr, sizeof(s_dst_node.mac_addr));
}
void set_dst_node_ipv6_addr(const char* ipv6_addr)
{
    memcpy(s_dst_node.ipv6_addr, ipv6_addr, sizeof(s_dst_node.ipv6_addr));
}

void get_dst_node_ipv6_addr(char* ipv6_addr)
{
    memcpy(ipv6_addr, s_dst_node.ipv6_addr, sizeof(s_dst_node.ipv6_addr));
}

void set_dst_node_handle(const char* handle)
{
    memcpy(s_dst_node.handle, handle, sizeof(s_dst_node.handle));
}

void get_dst_node_handle(char* handle)
{
    memcpy(handle, s_dst_node.handle, sizeof(s_dst_node.handle));
}

void set_dst_node_port(const char* port)
{
    memcpy(s_dst_node.port, port, sizeof(s_dst_node.port));
}

void get_dst_node_port(char* port)
{
    memcpy(port, s_dst_node.port, sizeof(s_dst_node.port));
}

void set_dst_node_security(const char* security)
{
    memcpy(s_dst_node.security, security, sizeof(s_dst_node.security));
}

void get_dst_node_security(char* security)
{
    memcpy(security, s_dst_node.security, sizeof(s_dst_node.security));
}

void set_dst_node_side(const char* side)
{
    memcpy(s_dst_node.side, side, sizeof(s_dst_node.side));
}

void get_dst_node_side(char* side)
{
    memcpy(side, s_dst_node.side, sizeof(s_dst_node.side));
}


void set_src_node_handle(const char* handle)
{
    memcpy(s_src_node.handle, handle, sizeof(s_src_node.handle));
}

void get_src_node_handle(char* handle)
{
    memcpy(handle, s_src_node.handle, sizeof(s_src_node.handle));
}

void set_dst_node_channel(const char* ch)
{
    memcpy(s_dst_node.channel, ch, sizeof(s_dst_node.channel));
}

void get_dst_node_channel(char* ch)
{
    memcpy(ch, s_dst_node.channel, sizeof(s_dst_node.channel));
}

void set_dst_node_pair_id(const char* pair_id)
{
    memcpy(s_dst_node.pairID, pair_id, sizeof(s_dst_node.pairID));
}

void get_dst_node_pair_id(char* pair_id)
{
    memcpy(pair_id, s_dst_node.pairID, sizeof(s_dst_node.pairID));

}

void set_dst_node_channel_page(char* channel_page)
{
    memcpy(s_dst_node.channel_page, channel_page, sizeof(s_dst_node.channel_page));
}

void get_dst_node_channel_page(char* channel_page)
{
    memcpy(channel_page, s_dst_node.channel_page, sizeof(s_dst_node.channel_page));
}

void set_dst_node_pan_id(const char* pan_id)
{
    memcpy(s_dst_node.pan_id, pan_id, sizeof(s_dst_node.pan_id));
}

void get_dst_node_pan_id(char* pan_id)
{
    memcpy(pan_id, s_dst_node.pan_id, sizeof(s_dst_node.pan_id));
}

void set_dst_node_lqi(const char* lqi)
{
    memcpy(s_dst_node.lqi, lqi, sizeof(s_dst_node.lqi));
}

void get_dst_node_lqi(char* lqi)
{
    memcpy(lqi, s_dst_node.lqi, sizeof(s_dst_node.lqi));
}



void calc_data_len(const char* payload, char* data_len)
{
    uint8_t index = (uint8_t)0;  // 
    uint8_t payload_len  = (uint8_t)0;   // 
    char  data_len_buf[MAX_DATA_LEN_SIZE] = {'\0'};
    char  zero_pad[MAX_ZERO_PAD_SIZE] = {'\0'};

    payload_len = strlen(payload);

    // fill with "0"
    for(index = (uint8_t)0; index < (uint8_t)SKSENDTO_FMT_DATA_LEN - (uint8_t)(payload_len/0x0F) - 1; index++) {
        zero_pad[index] = '0';
    }
    strcat(data_len, zero_pad);

    // convert into char in hexadecimal
    sprintf(data_len_buf, "%X", payload_len);
    strcat(data_len, data_len_buf);
}


/*************************************************************************//**
 * @brief 
 * 
 * @param payload 
 * @param packet 
 ****************************************************************************/
void make_send_packet(const char* payload , PACKET_T* packet)
{
    SKSENDTO_T buf;

    memset(&buf, '\0', sizeof(buf));

    // add SKSENDTO command length to packet
    strcat(packet->data, BP35A1_CMD_SKSENDTO);
    strcat(packet->data, DELIM_SPACE);
    
    // add handle to packet
    get_src_node_handle(buf.handle);
    strcat(packet->data, buf.handle);
    strcat(packet->data, DELIM_SPACE);

    // add IPv6 address to packet
    get_dst_node_ipv6_addr(buf.ipv6_addr);
    strncat(packet->data, buf.ipv6_addr, IPV6_ADDR_LEN-1);
    strcat(packet->data, DELIM_SPACE);


    // add port to packet
    get_dst_node_port(buf.port);
    strcat(packet->data, buf.port);
    strcat(packet->data, DELIM_SPACE);


    // add security to packet
    get_dst_node_security(buf.security);
    strcat(packet->data, buf.security);
    strcat(packet->data, DELIM_SPACE);

    // add active side to packet
    get_dst_node_side(buf.side);
    strcat(packet->data, buf.side);
    strcat(packet->data, DELIM_SPACE);
    
    // calculate payload length
    calc_data_len(payload, buf.data_len);

    // add payload length to packet
    strcat(packet->data, buf.data_len);
    strcat(packet->data, DELIM_SPACE);
        
    // add payload to packet
    strcat(packet->data, payload);
    
}

void send_packet(const char* payload)
{
    Serial.flush();
    Serial1.flush();

    Serial.println(payload);
    Serial1.println(payload);
}
