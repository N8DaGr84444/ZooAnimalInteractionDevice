/*************
 * SDA - SDA *
 * SCL - SCL *
 * VCC - 5V  *
 * GND - GND *
 *************/

#include "RTClib.h"

RTC_DS3231 rtc;

void initRTC(void)
{
  if(!rtc.begin()) return;

  if(rtc.lostPower())
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
}

String getTs(void)
{
  return rtc.now().timestamp(DateTime::TIMESTAMP_FULL);
}
