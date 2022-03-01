/***************************************
 * Senior Design II - Transmitter Code *
 ***************************************/

void initDFac(void);
uint8_t getDFac(void);
void setDFac(int cVal);
void initEnc(void);
void initDisp(void);
void dispDFac(uint8_t dVal);

static uint8_t lastDFac = -1;

void setup()
{
  const uint8_t D_FAC = getDFac();
  if (D_FAC > 100 || D_FAC < 0)
    initDFac();
  initEnc();
  initDisp();
}

void loop()
{
  uint8_t curDFac = getDFac();
  if (curDFac != lastDFac)
  {
    dispDFac(curDFac);
    lastDFac = curDFac;
  }
}
