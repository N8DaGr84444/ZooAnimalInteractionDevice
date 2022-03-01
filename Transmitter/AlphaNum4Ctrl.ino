/*************
 * CLK - SCL *
 * DAT - SDA *
 * GND - GND *
 * VCC - 5V  *
 * Vi2c - 5V *
 *************/

#include <Wire.h>
#include <Adafruit_GFX.h>
#include "Adafruit_LEDBackpack.h"

static Adafruit_AlphaNum4 alpha4 = Adafruit_AlphaNum4();

void initDisp(void)
{
  alpha4.begin(0x70);
}

void dispDFac(uint8_t dVal)
{
  char dBuf[4];
  sprintf(dBuf, "%i", dVal);

  uint8_t alpha4Inx = 3;
  alpha4.clear();
  for (int i = strlen(dBuf) - 1; i >= 0; i--)
    alpha4.writeDigitAscii(alpha4Inx--, dBuf[i]);
  alpha4.writeDisplay();
}
