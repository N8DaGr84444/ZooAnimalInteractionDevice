/*******************************
 * Senior Design II - Receiver *
 *******************************/

void initRTC(void);
String getTs(void);
void initSD(void);
void logData(String ts);

static const uint8_t RECV_IN_PIN = 2;
static bool sigRecved = false;

void setup()
{
  initRTC();
  initSD();
  pinMode(RECV_IN_PIN, INPUT);
  digitalWrite(RECV_IN_PIN, LOW);
  attachInterrupt(digitalPinToInterrupt(RECV_IN_PIN), RECV_ISR, RISING);
}

void loop()
{
  if (sigRecved)
  {
    logData(getTs());
    sigRecved = false;
  }
}

void RECV_ISR(void)
{
  sigRecved = true;
}
