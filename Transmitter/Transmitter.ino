/***************************************
 * Senior Design II - Transmitter Code *
 ***************************************/

// Initialize components
void initMotionShield(void);

void initDFac(void);
uint8_t getDFac(void);
void setDFac(int cVal);
void initEnc(void);
void initDisp(void);
void dispDFac(uint8_t dVal);

static uint8_t lastDFac = -1;   // Hold last motion threshold value


void setup()
{
  // Initialize Serial Port
  Serial.begin(115200);
  Serial.println("Zoo Animal Interactive Decice");
  Serial.println("Created in 2022 as a University of Cincinnati Capstone Project");
  Serial.println("Built by Nate Alter and Ojas Anand");
  Serial.println("Git repo: https://github.com/JJuiice/Senior-Design");
  Serial.println("-------------------------------------------------------------");
  Serial.println();
  Serial.println();

  // Initialize I2C communication for the motion sensor
  I2C.begin();

  // Setup 4 digit display
  const uint8_t D_FAC = getDFac();
  if (D_FAC > 100 || D_FAC < 0)
    initDFac();
  initEnc();
  initDisp();

  // Motion Sensor Initialization
  Serial.println("Please wait. Motion sensor initialization in progress.");
  setupMotionShield();

  // Attach interrupt to Interrupt Service Routine
  // for a Rising Edge. Change the interrupt pin depending on the board.
  attachInterrupt(INT_PIN, motionISR, RISING);
  
  /// Print ready message
  Serial.println("Initialization complete, system is ready.");
  Serial.println("-------------------------------------------------------------");
  Serial.println();
  Serial.println();
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
