/*******************************
 * Senior Design II - Receiver *
 *******************************/

void initRTC(void);
String getTs(void);
void initSD(void);
void logData(String ts);

static const uint8_t RECV_IN_PIN = 2;

void setup() {
  Serial.begin(115200);
  while(!Serial) delay(250);
  Serial.println("Serial Ready");
  
  initRTC();
  initSD();
  pinMode(RECV_IN_PIN, INPUT);
  digitalWrite(RECV_IN_PIN, LOW);
  attachInterrupt(digitalPinToInterrupt(RECV_IN_PIN), RECV_ISR, RISING);
}

void loop() {
  delay(100);
}

void RECV_ISR(void)
{
  Serial.println("RECV_ISR");
  //logData(getTs());
}
