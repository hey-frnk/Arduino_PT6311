#include <SPI.h>
#include "pt6311.h"

#define VFDCO_PT6311_SS_PIN_ARDUINO 10

struct _vfdco_pt6311_device{
  uint8_t num_digits;
  vfdco_pt6311_display_state_t state;
  vfdco_pt6311_brightness_t brightness;
} vfdco_pt6311_device;

void _vfdco_pt6311_set_data(uint8_t data) {
  digitalWrite(VFDCO_PT6311_SS_PIN_ARDUINO, LOW);
  SPI.transfer(data);
  digitalWrite(VFDCO_PT6311_SS_PIN_ARDUINO, HIGH);
}

void vfdco_pt6311_init(uint8_t num_digits) {
  vfdco_pt6311_device.num_digits = num_digits;

  pinMode(VFDCO_PT6311_SS_PIN_ARDUINO, OUTPUT);

  digitalWrite(VFDCO_PT6311_SS_PIN_ARDUINO, HIGH);
  SPI.begin();
  SPI.setBitOrder(LSBFIRST);
  SPI.setClockDivider(SPI_CLOCK_DIV128);
  SPI.setDataMode(SPI_MODE3);

  _vfdco_pt6311_set_data(
    (uint8_t)VFDCO_PT6311_COMMAND_2 
    | (uint8_t)VFDCO_PT6311_OP_MODE_NORMAL 
    | (uint8_t)VFDCO_PT6311_ADDR_MODE_INCR 
    | (uint8_t)VFDCO_PT6311_RW_MODE_WRITE_DISPLAY
  );
  digitalWrite(VFDCO_PT6311_SS_PIN_ARDUINO, LOW);

  SPI.transfer((uint8_t)VFDCO_PT6311_COMMAND_3);

  for(volatile uint8_t i = 0; i < 13; ++i) {
    SPI.transfer(0);
    SPI.transfer(0);
    SPI.transfer(0);
  }
  digitalWrite(VFDCO_PT6311_SS_PIN_ARDUINO, HIGH);
  delayMicroseconds(25);

  switch(num_digits) {
    case 9:   _vfdco_pt6311_set_data((uint8_t)VFDCO_PT6311_COMMAND_1 | (uint8_t)VFDCO_PT6311_DIG9_SEG19);   break;
    case 10:  _vfdco_pt6311_set_data((uint8_t)VFDCO_PT6311_COMMAND_1 | (uint8_t)VFDCO_PT6311_DIG10_SEG18);  break;
    case 11:  _vfdco_pt6311_set_data((uint8_t)VFDCO_PT6311_COMMAND_1 | (uint8_t)VFDCO_PT6311_DIG11_SEG17);  break;
    case 12:  _vfdco_pt6311_set_data((uint8_t)VFDCO_PT6311_COMMAND_1 | (uint8_t)VFDCO_PT6311_DIG12_SEG16);  break;
    case 13:  _vfdco_pt6311_set_data((uint8_t)VFDCO_PT6311_COMMAND_1 | (uint8_t)VFDCO_PT6311_DIG13_SEG15);  break;
    case 14:  _vfdco_pt6311_set_data((uint8_t)VFDCO_PT6311_COMMAND_1 | (uint8_t)VFDCO_PT6311_DIG14_SEG14);  break;
    case 15:  _vfdco_pt6311_set_data((uint8_t)VFDCO_PT6311_COMMAND_1 | (uint8_t)VFDCO_PT6311_DIG15_SEG13);  break;
    case 16:  _vfdco_pt6311_set_data((uint8_t)VFDCO_PT6311_COMMAND_1 | (uint8_t)VFDCO_PT6311_DIG16_SEG12);  break;
    default:  _vfdco_pt6311_set_data((uint8_t)VFDCO_PT6311_COMMAND_1 | (uint8_t)VFDCO_PT6311_DIG8_SEG20);   break;
  }
  vfdco_pt6311_device.state = VFDCO_PT6311_DISPLAY_STATE_ON;
  vfdco_pt6311_device.brightness = VFDCO_PT6311_PULSE_WIDTH_8;
  _vfdco_pt6311_set_data((uint8_t)VFDCO_PT6311_COMMAND_4 | (uint8_t)vfdco_pt6311_device.state | (uint8_t)vfdco_pt6311_device.brightness);
}



void vfdco_pt6311_set_brightness(vfdco_pt6311_brightness_t brightness) {
  vfdco_pt6311_device.brightness = brightness;
  _vfdco_pt6311_set_data(VFDCO_PT6311_COMMAND_4 | (uint8_t)vfdco_pt6311_device.state | (uint8_t)brightness);
}

void vfdco_pt6311_set_state(vfdco_pt6311_display_state_t state) {
  vfdco_pt6311_device.state = state;
  _vfdco_pt6311_set_data(VFDCO_PT6311_COMMAND_4 | (uint8_t)state | (uint8_t)vfdco_pt6311_device.brightness);
}

void vfdco_pt6311_set_data(uint8_t digit_pos, uint32_t data) {
  _vfdco_pt6311_set_data(
    (uint8_t)VFDCO_PT6311_COMMAND_2 
    | (uint8_t)VFDCO_PT6311_OP_MODE_NORMAL 
    | (uint8_t)VFDCO_PT6311_ADDR_MODE_INCR 
    | (uint8_t)VFDCO_PT6311_RW_MODE_WRITE_DISPLAY
  );
  digitalWrite(VFDCO_PT6311_SS_PIN_ARDUINO, LOW);
  SPI.transfer((uint8_t)VFDCO_PT6311_COMMAND_3 | (digit_pos * 0x03));
  SPI.transfer((uint8_t)(data      ));
  SPI.transfer((uint8_t)(data >>  8));
  SPI.transfer((uint8_t)(data >> 16));
  digitalWrite(VFDCO_PT6311_SS_PIN_ARDUINO, HIGH);
}

uint8_t vfdco_pt6311_get_sw() {
  digitalWrite(VFDCO_PT6311_SS_PIN_ARDUINO, LOW);
  SPI.transfer(
    (uint8_t)VFDCO_PT6311_COMMAND_2 
    | (uint8_t)VFDCO_PT6311_OP_MODE_NORMAL 
    | (uint8_t)VFDCO_PT6311_ADDR_MODE_INCR
    | (uint8_t)VFDCO_PT6311_RW_MODE_READ_SW
  );
  uint8_t sw_in = SPI.transfer(0xFF) & 0x0F;
  digitalWrite(VFDCO_PT6311_SS_PIN_ARDUINO, HIGH);

  return sw_in;
}