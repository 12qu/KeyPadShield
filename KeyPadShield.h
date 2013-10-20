#ifndef KEYPADSHIELD_H
#define KEYPADSHIELD_H

#include <LiquidCrystal.h>

/**
 * Basic wrapper for the DFRobot KeyPad Shield to use the LiquidCrystal library
 * without worrying about pinouts etc. Pins taken from:
 * http://www.dfrobot.com/wiki/images/a/a7/LCDKeypad_Shield_SCH.png
 *
 * Note that all indexing of rows and columns is done starting from 0.
 */
class KeyPadShield : public LiquidCrystal {
  public:
    KeyPadShield() : LiquidCrystal(RS_PIN, E_PIN, D0_PIN, D1_PIN, D2_PIN, D3_PIN) {};

    /**
     * Initialize KeyPadShield
     */
    void begin() { LiquidCrystal::begin(COLUMNS, ROWS); };

    /**
     * Clears the specified row from column specified to the last column
     */
    void clearRowFrom(uint8_t row, uint8_t column);
    void clearRow(uint8_t row) { clearRowFrom(row, 0); };

    /**
     * Formatted print to row. Note that there is a limit to the number of
     * characters that will be printed (40 for v1.1). Returns the number of
     * characters printed.
     */
    int fprintf(uint8_t row, const char* format, ...);

    enum ButtonCode { NONE, RIGHT, UP, DOWN, LEFT, SELECT };
    ButtonCode getButtonPress();

  private:
    /* Dimensions for display. HD44780U has 80 character buffer which can be
     * written to -- addresses 0x00 to 0x27 will be displayed on the first row
     * (though only 16 will be visible), and 0x40 to 0x67 on the second row.
     */
    static constexpr uint8_t
      COLUMNS = 40,
      ROWS = 2;

    /* Arduino digital pins connecting to ports on the HD44780U */
    static constexpr uint8_t
      RS_PIN = 8,
      E_PIN  = 9,
      // In v1.1, used pins start at DB4 (DB0-DB3 are unused) but LiquidCrystal
      // will still treat these pins as if they were DB0-DB3
      D0_PIN = 4,
      D1_PIN = 5,
      D2_PIN = 6,
      D3_PIN = 7;

};

#endif /* KEYPADSHIELD_H */
