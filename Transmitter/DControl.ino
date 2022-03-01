/*************
 * VCC - 5V  *
 * GND - GND *
 * CLK - D3  *
 * DT - D4   *
 *************/
 
static const uint8_t PIN_A = 3;
static const uint8_t PIN_B = 4;

void initEnc(void)
{
  pinMode (PIN_A, INPUT);
  pinMode (PIN_B, INPUT);
  digitalWrite(PIN_A, HIGH);
  digitalWrite(PIN_B, HIGH);
  attachInterrupt(digitalPinToInterrupt(PIN_A), checkEnc, CHANGE);
}

void checkEnc(void)
{
  if (digitalRead(PIN_A) == HIGH)
    if (digitalRead(PIN_B) != LOW)
      setDFac(-1);
    else
      setDFac(1);
  else
    if (digitalRead(PIN_B) == LOW)
      setDFac(-1);
    else
      setDFac(1);
} 
