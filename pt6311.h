#ifndef PT6311_H
#define PT6311_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

typedef enum {
  VFDCO_PT6311_COMMAND_1      = 0b00000000,
  VFDCO_PT6311_COMMAND_2      = 0b01000000,
  VFDCO_PT6311_COMMAND_3      = 0b11000000,
  VFDCO_PT6311_COMMAND_4      = 0b10000000
} vfdco_pt6311_command_t;

// Command type 1
typedef enum {
  VFDCO_PT6311_DIG8_SEG20     = 0b0000,
  VFDCO_PT6311_DIG9_SEG19     = 0b1000,
  VFDCO_PT6311_DIG10_SEG18    = 0b1001,
  VFDCO_PT6311_DIG11_SEG17    = 0b1010,
  VFDCO_PT6311_DIG12_SEG16    = 0b1011,
  VFDCO_PT6311_DIG13_SEG15    = 0b1100,
  VFDCO_PT6311_DIG14_SEG14    = 0b1101,
  VFDCO_PT6311_DIG15_SEG13    = 0b1110,
  VFDCO_PT6311_DIG16_SEG12    = 0b1111
} vfdco_pt6311_digit_segment_t;

// Command type 2: operation mode
typedef enum {
  VFDCO_PT6311_OP_MODE_NORMAL = 0b0000,
  VFDCO_PT6311_OP_MODE_TEST   = 0b0000
} vfdco_pt6311_op_mode_t;

// Command type 2: address mode
typedef enum {
  VFDCO_PT6311_ADDR_MODE_INCR     = 0b000,
  VFDCO_PT6311_ADDR_MODE_FIXED    = 0b100
} vfdco_pt6311_addr_mode_t;

// Command type 2: read/write mode
typedef enum {
  VFDCO_PT6311_RW_MODE_WRITE_DISPLAY     = 0b00,
  VFDCO_PT6311_RW_MODE_WRITE_LED         = 0b01,
  VFDCO_PT6311_RW_MODE_READ_KEY          = 0b10,
  VFDCO_PT6311_RW_MODE_READ_SW           = 0b11
} vfdco_pt6311_rw_mode_t;

// Command type 4: display on/off
typedef enum {
  VFDCO_PT6311_DISPLAY_STATE_OFF     = 0b0000,
  VFDCO_PT6311_DISPLAY_STATE_ON      = 0b1000
} vfdco_pt6311_display_state_t;

// Command type 4: display PWM duty cycle (brightness). 1: min, 8: max
typedef enum {
  VFDCO_PT6311_PULSE_WIDTH_1    = 0b000,
  VFDCO_PT6311_PULSE_WIDTH_2    = 0b001,
  VFDCO_PT6311_PULSE_WIDTH_3    = 0b010,
  VFDCO_PT6311_PULSE_WIDTH_4    = 0b011,
  VFDCO_PT6311_PULSE_WIDTH_5    = 0b100,
  VFDCO_PT6311_PULSE_WIDTH_6    = 0b101,
  VFDCO_PT6311_PULSE_WIDTH_7    = 0b110,
  VFDCO_PT6311_PULSE_WIDTH_8    = 0b111
} vfdco_pt6311_brightness_t;

// Public:
void vfdco_pt6311_init(uint8_t num_digits);

void vfdco_pt6311_set_brightness(vfdco_pt6311_brightness_t brightness);
void vfdco_pt6311_set_state(vfdco_pt6311_display_state_t state);
void vfdco_pt6311_set_data(uint8_t digit_pos, uint32_t data);

uint8_t vfdco_pt6311_get_sw();

#ifdef __cplusplus
}
#endif

#endif