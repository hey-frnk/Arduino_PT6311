#ifndef VFDCO_8D14S_H
#define VFDCO_8D14S_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

#define VFDCO_8D14S_OVERLAY_DP_LEFT     0b0010000000000000
#define VFDCO_8D14S_OVERLAY_DP_RIGHT    0b1000000000000000

#define VFDCO_8D14S_OVERLAY_COL_LEFT    0b1000000000000000
#define VFDCO_8D14S_OVERLAY_COL_CENTER  0b0010000000000000
#define VFDCO_8D14S_OVERLAY_COL_RIGHT   0b0010000000000000

void vfdco_8d14s_init();

void vfdco_8d14s_write_char(uint8_t digit_position, char character);
void vfdco_8d14s_write_char_with_overlay(uint8_t digit_position, char character, uint16_t overlay);

void vfdco_8d14s_write_string(char *text);
// Multi bit overlay 0b[0|0|0|DPL|DPR|COL|COC|COR]
void vfdco_8d14s_write_string_with_overlay(char *text, uint8_t overlay);

#ifdef __cplusplus
}
#endif

#endif