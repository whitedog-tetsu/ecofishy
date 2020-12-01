#ifndef SYSTEM_H
#define SYSTEM_H

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

#include <stdint.h>

/**
 <bit>

 <2> : update config
 <1> : system Config
 <0> : BP35A1 wakeup
*/
#define ERR_BIT_WKUP_BP35A1  0x01
#define ERR_BIT_INQ_CONF     0x11
#define ERR_BIT_UPDATE_CONF  0x21

#define MAX_NUM_OF_DEVICE    (5)

#define STR_COMPUTE_WAIT_TIME "COMPUTE_WAIT_TIME"
#define STR_OP_MODE "OP_MODE"


typedef enum result_t {
    OK = 0,
    NG = -1
} RESULT_T;

typedef enum op_state_t {
    INIT_STATE            = 0x00, ///< initialize state
    COMPUTE_INIT_STATE    = 0x10, ///< control state
    COMPUTE_MEASURE_STATE = 0x11, ///< measure temperature state. 0x02 to 0x0F is reserved.
    COMPUTE_WAIT_STATE    = 0x12, ///< wait state. 
    OP_STATE_DEFAULT      = 0xFF  ///< default state value
} OP_STATE_T;


typedef enum op_mode_t {
   HOST_MODE    = 0x00,
   SENSOR_MODE  = 0x01,
   DEFAULT_MODE = 0xFF
} OP_MODE_T;


/*************************************************************************//**
 * @brief 
 *               bit 7 6 5 4 3 2 1 0
 *   TEMPERATURE     r r r r 0 0 0 0    num of temperature sensor
 *   Humidity
 * 
 ****************************************************************************/
typedef struct NODE_TYPE_T {
    uint8_t temperature_sensor;
    uint8_t ph_sensor;
    uint8_t salt_sensor;
} NODE_TYPE_T;

typedef struct node_config_t {
   NODE_TYPE_T node_type[MAX_NUM_OF_DEVICE];
   uint16_t wait_time;
   uint8_t  power_mode;
   OP_MODE_T op_mode;
   uint8_t  device_handle;
} NODE_CONFIG_T;

typedef struct data_temperature16_t {
    uint16_t src1;
    uint16_t src2;
    uint16_t src3;
} DATA_TEMPERATURE16_T;

typedef struct data_temperature32_t {
    int32_t src1;
    int32_t src2;
    int32_t src3;
} DATA_TEMPERATURE32_T;

typedef struct data_temperature32f_t {
    double src1;
    double src2;
    double src3;
} DATA_TEMPERATURE32F_T;


extern void sensor_mode(void);
extern void host_mode(void);

extern OP_STATE_T get_last_state(void);
extern void       set_last_state(const OP_STATE_T state);

extern OP_STATE_T get_next_state(void);
extern void       set_next_state(const OP_STATE_T state);

extern void system_setup_uart(void);
extern void system_setup_i2c(void);
extern RESULT_T wakeup_bp35a1(void);
extern RESULT_T check_awaken_bp35a1(void);
extern RESULT_T inquire_sensor_node_config(void);
extern RESULT_T update_sensor_node_config(void);
extern RESULT_T sleep_bp35a1(void);


extern void set_err_bit(const uint8_t err_bit);
extern uint8_t get_err_bit(const uint8_t err_bit);
extern void clear_err_bit(const uint8_t err_bit);
extern void init_err_bit(void);
extern uint16_t get_err_code(void);


extern void inc_sequence_num(uint8_t step);
extern void dec_sequence_num(uint8_t step);
extern uint8_t get_sequence_num(void);
extern void set_sequence_num(const uint8_t seq_num);
extern void init_sequence_num(void);

extern void software_reset(void);
extern void clear_serial_buf(void);

extern void get_compute_wait_time(uint16_t* wait_time);
extern void set_compute_wait_time(const uint16_t wait_time);
extern void get_compute_op_mode(OP_MODE_T* op_mode);
extern void set_compute_op_mode(const OP_MODE_T op_mode);
extern RESULT_T set_sensor_node_config(const NODE_CONFIG_T* data);
extern RESULT_T get_sensor_node_config(NODE_CONFIG_T* data);

extern void ecofishy_config_parse(const char* config);
//extern void ecofishy_config_parse_str(const String& config);


#ifdef __cplusplus
}
#endif // __cplusplus

#endif // SYSTEM_H
