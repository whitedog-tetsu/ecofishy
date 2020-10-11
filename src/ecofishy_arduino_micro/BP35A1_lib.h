#ifndef BP35A1_LIB_H
#define BP35A1_LIB_H

#include <stdint.h>
#include "system.h"

#ifdef __cplusplus
extern "C" {
#endif



#define BP35A1_CMD_SKINFO    "SKINFO"
#define BP35A1_CMD_SKVER     "SKVER"
#define BP35A1_CMD_SKPING    "SKPING"
#define BP35A1_CMD_SKSENDTO  "SKSENDTO"
#define BP35A1_CMD_SKRESET   "SKRESET"
#define BP35A1_CMD_SKDSLEEP  "SKDSLEEP"
#define BP35A1_CMD_SKSTART   "SKSTART"
#define BP35A1_CMD_SKSCAN    "SKSCAN"
#define BP35A1_CMD_SKLL64    "SKLL64"
#define DELIM_SPACE          " "
#define DELIM_COMMA          ","
#define BP35A1_CMD_NEWLINE   '\n'
#define BP35A1_CMD_EOL       '\0'

#define BP35A1_UDP_PORT_HNDL_ECHONET_LITE  "1"    ///< UDP port handle ECHONET Lite
#define BP35A1_UDP_PORT_HNDL_PANA          "2"    ///< UDP port handle PANA
#define BP35A1_UDP_PORT_HNDL_MLE           "3"    ///< UDP port handle MLE
#define BP35A1_UDP_PORT_HNDL_USER1         "4"    ///< UDP port handle user defined 1
#define BP35A1_UDP_PORT_HNDL_USER2         "5"    ///< UDP port handle user defined 2
#define BP35A1_UDP_PORT_HNDL_USER3         "6"    ///< UDP port handle user defined 3

#define BP35A1_UDP_PORT_ECHONET_LITE       "0E1A"  ///< port 3610(decimal)
#define BP35A1_UDP_PORT_PANA               "2CC"   ///< port 716(decimal)
#define BP35A1_UDP_PORT_MLE                "4D4C"  ///< port 19788(decimal)

#define BP35A1_SECURITY_ACTIVE             "1"     ///< security active
#define BP35A1_SECURITY_INACTIVE           "0"     ///< security inactive

#define BP35A1_SIDE_ROUTE_B                "0"     ///< active side Route B
#define BP35A1_SIDE_HAN                    "1"     ///< active side HAN

#define BP35A1_CMD_SKSENDTO_LEN  (sizeof(BP35A1_CMD_SKSENDTO)+1) // 8byte

#define IPV6_ADDR_LEN      (40) //39 + 1 = FE80:xxxx:xxxx:xxxx:xxxx:xxxx:xxxx:xxxx + \0
#define MAC_ADDR_LEN       (16) 
#define SKSENDTO_FMT_DATA_LEN  (4)
#define CHANNEL_LEN  (2)
#define SIDE_LEN     (1)
#define PORT_LEN     (4)
#define HANDLE_LEN   (2)
#define SECURITY_LEN (1)
#define PAYLOAD_LEN  (16)
#define CHANNEL_PAGE_LEN (2)
#define PAIR_ID_LEN      (8)
#define LQI_LEN          (2)
#define PAN_ID_LEN       (2)

#define MAX_DATA_LEN_SIZE  (4)
#define MAX_ZERO_PAD_SIZE  (4)

#define BP35A1_CMD_SKINFO_RECV_LINE    (3)
#define BP35A1_CMD_SKVER_RECV_LINE     (3)
#define BP35A1_CMD_SKPING_RECV_LINE    (4)
#define BP35A1_CMD_SKSENDTO_RECV_LINE  (3)
#define BP35A1_CMD_SKRESET_RECV_LINE   (2)
#define BP35A1_CMD_SKDSLEEP_RECV_LINE  (2)
#define BP35A1_CMD_SKSTART_RECV_LINE   (2)
#define BP35A1_CMD_SKSCAN_RECV_LINE    (8)

typedef struct bp35a1_cmd_t {
    const char* skcmd;
    char* param0;
    char* param1;
    char* param2;
    char* param3;
    char* param4;
    char* param5;
    char* param6;
    char* param7;
    uint8_t recv_line;
} BP35A1_CMD_T;

typedef struct bp35a1_node_t {
    char ipv6_addr[IPV6_ADDR_LEN];
    char mac_addr[MAC_ADDR_LEN];
    char channel[CHANNEL_LEN];
    char side[SIDE_LEN];
    char port[PORT_LEN];
    char handle[HANDLE_LEN];
    char security[SECURITY_LEN];
    char pairID[PAIR_ID_LEN];
    char lqi[LQI_LEN];
    char pan_id[PAN_ID_LEN];
    char channel_page[CHANNEL_PAGE_LEN];
} BP35A1_NODE_T;

typedef struct sksendto_t {
    char cmd[BP35A1_CMD_SKSENDTO_LEN];    ///< SK command 9 bytes
    char handle[HANDLE_LEN];              ///< handle 2 bytes
    char ipv6_addr[IPV6_ADDR_LEN];        ///< IPv6 address 40 bytes
    char port[PORT_LEN];                  ///< port 5 bytes
    char security[SECURITY_LEN];          ///< security 2 bytes
    char side[SIDE_LEN];                  ///< side 2 bytes
    char data_len[SKSENDTO_FMT_DATA_LEN]; ///< data length 5 bytes
    char payload[PAYLOAD_LEN];            ///< payload 33 bytes
} SKSENDTO_T;

#define MAX_PACKET_LEN sizeof(SKSENDTO_T)

typedef struct pakcet_t {
    char data[MAX_PACKET_LEN];  // size 1287 bytes
    uint8_t dlen;
} PACKET_T;



extern BP35A1_CMD_T bp35a1_cmd_set[8];

extern RESULT_T BP35A1_reset(char* buf, uint8_t* buf_size);
extern RESULT_T BP35A1_scan_dst_device(char* buf, uint8_t* buf_size);
extern RESULT_T BP35A1_check_fw_version(char* buf, uint8_t* buf_size);

extern void convert_mac_ipv6(const char* mac_addr, char* ipv6_addr);

extern RESULT_T BP35A1_cmd_send(const BP35A1_CMD_T* cmd, const uint32_t timeout_msec, char* readbuf, uint8_t* readbuf_size);

extern void init_dst_node_info(void);
extern void set_dst_node_info(const BP35A1_NODE_T* dst_node);
extern void get_dst_node_info(BP35A1_NODE_T* dst_node);

extern void set_dst_node_mac_addr(const char* mac_addr);
extern void get_dst_node_mac_addr(char* mac_addr);

extern void set_dst_node_ipv6_addr(const char* ipv6_addr);
extern void get_dst_node_ipv6_addr(char* ipv6_addr);

extern void set_dst_node_handle(const char* handle);
extern void get_dst_node_handle(char* handle);

extern void set_dst_node_port(const char* port);
extern void get_dst_node_port(char* port);

extern void set_dst_node_security(const char* security);
extern void get_dst_node_security(char* security);

extern void set_dst_node_side(const char* side);
extern void get_dst_node_side(char* side);

extern void set_src_node_handle(const char* handle);
extern void get_src_node_handle(char* handle);

extern void set_dst_node_channel(const char* ch);
extern void get_dst_node_channel(char* ch);

extern void set_dst_node_channel_page(char* channel_page);
extern void get_dst_node_channel_page(char* channel_page);

extern void set_dst_node_pair_id(const char* pair_id);
extern void get_dst_node_pair_id(char* pair_id);

extern void set_dst_node_pan_id(const char* pan_id);
extern void get_dst_node_pan_id(char* pan_id);

extern void set_dst_node_lqi(const char* lqi);
extern void get_dst_node_lqi(char* lqi);

extern void make_send_packet(const char* payload, PACKET_T* packet);
extern void send_packet(const char* payload);

extern void calc_data_len(const char* payload, char* data_len);


#ifdef __cplusplus
}
#endif // __cplusplus


#endif // BP35A1_LIB_H