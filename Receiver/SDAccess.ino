/**************
 * MOSI - D11 *
 * MISO - D12 *
 * SCK - D13  *
 * CS - D10   *
 **************/

#include <SPI.h>
#include <SD.h>

void initSD(void)
{
 if(!SD.begin(4)) return;
}

void logData(String ts)
{
 File actLog = SD.open("activity_log.txt", FILE_WRITE);

 if (actLog)
 {
   actLog.println(ts);
   actLog.close();
 }
}
