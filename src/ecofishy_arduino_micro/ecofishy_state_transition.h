#ifndef ECOFISHY_STATE_TRANSITION_H
#define ECOFISHY_STATE_TRANSITION_H


//#include <Arduino.h>
#include "system.h"
#include <stdint.h>


#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

#define MAX_DATA_TEMPER_SIZE     (100)
#define SUM_DATA_TEMPER_SIZE     (MAX_DATA_TEMPER_SIZE)
#define AVERAGE_DATA_TEMPER_SIZE (SUM_DATA_TEMPER_SIZE)
#define ROUND_DATA_TEMPER_DIGIT  (AVERAGE_DATA_TEMPER_SIZE/2)
#define WAIT_TIME_EVENT22        (20000)
#define WAIT_STARTUP_BP35A1      (3000)
#define BUF_SIZE  64
#ifndef MAC_ADDR_LEN
  #define MAC_ADDR_LEN (16)
#endif // MAC_ADDR_LEN

#define MAC_ADDR_READ_BYTE_START_POS (144)
#define MAC_ADDR_READ_BYTE_END_POS   (MAC_ADDR_READ_BYTE_START_POS + MAC_ADDR_LEN)

#define MAX_CONNECTION_RETRY   (0)
#define WAIT_TIME_INIT_ACK     (3000)  ///< 3000msec
#define WAIT_TIME_ACK          (1000)  ///< 1000msec

#define DEFAULT_COMP_WAIT_TIME (3000)

typedef struct measure_temper_t {
    double temper_degc1;
    double temper_degc2;
} MEASURE_TEMPER_T;





extern void init_state(OP_STATE_T state);
extern void compute_init_state(OP_STATE_T state);


extern void send_char(char* buf);
extern void send_ready(void);
extern RESULT_T wait_char(char* packet, uint16_t time_msec);

extern void compute_measure_state(const OP_STATE_T state);
extern void compute_measure_temperature(MEASURE_TEMPER_T* data);
extern void round_temper_data(int32_t* data, int32_t digit);
extern RESULT_T start_compute_measure_state(void);
extern RESULT_T end_compute_measure_state(void);
extern RESULT_T search_dest_node(char* buf);





#ifdef __cplusplus
}
#endif // __cplusplus

#endif // ECOFISHY_STATE_TRANSITION_H
