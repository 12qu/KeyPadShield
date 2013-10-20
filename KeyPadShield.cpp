#include <stdarg.h>
#include <stdio.h>
#include <Arduino.h>
#include "KeyPadShield.h"
#include <Macros.h>

/**
 * Slightly modified version taken from:
 * http://www.dfrobot.com/wiki/index.php?title=Arduino_LCD_KeyPad_Shield_(SKU:_DFR0009)
 */
KeyPadShield::ButtonCode KeyPadShield::getButtonPress() {
  int adc_key_in = analogRead(0);      // read the value from the sensor
  // my buttons when read are centered at these valies: 0, 144, 329, 504, 741
  // we add approx 50 to those values and check to see if we are close
  if (adc_key_in > 1000) return NONE; // We make this the 1st option for speed reasons since it will be the most likely result
  if (adc_key_in < 50)   return RIGHT; 
  if (adc_key_in < 250)  return UP;
  if (adc_key_in < 450)  return DOWN;
  if (adc_key_in < 650)  return LEFT;
  if (adc_key_in < 850)  return SELECT; 

  return NONE;  // when all others fail, return this...
}

void KeyPadShield::clearRowFrom(uint8_t row, uint8_t column) {
  for (uint8_t i = column; i < COLUMNS; i++) {
    setCursor(i, row);
    write(' ');
  }
}

int KeyPadShield::fprintf(uint8_t row, const char* format, ...) {
  if (row >= ROWS)
    return -1;

  va_list args;
  size_t buffer_size = COLUMNS + 1; // 1 more space for null byte
  char buffer[buffer_size];

  va_start(args, format);
  int num_printed = vsnprintf(buffer, buffer_size, format, args);
  va_end(args);

  clearRowFrom(row, num_printed);
  setCursor(0, row);
  print(buffer);

  // Can't have printed more than COLUMNS characters
  return num_printed >= COLUMNS ? COLUMNS : num_printed;
}
