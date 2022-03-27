/***************************************
 * Senior Design II - Transmitter Code *
 ***************************************/

// Libraries
#include "Arduino_NineAxesMotion.h" //Contains the bridge code between the API and the Arduino Environment
#include <Wire.h>



// Initialize components
void initDFac(void);
uint8_t getDFac(void);
void setDFac(int cVal);
void initEnc(void);
void initDisp(void);
void dispDFac(uint8_t dVal);

static uint8_t lastDFac = -1;   // Hold last motion threshold value

// Initialize motion shield
NineAxesMotion motionSensor;  //Object that for the sensor
bool intDetected = false; //Flag to indicate if an interrupt was detected
int threshold = 100;      //At a Range of 4g, the threshold is set at 39.05mg or 0.3830m/s2. This Range is the default for NDOF Mode
int duration = 1;     //At a filter Bandwidth of 62.5Hz, the duration is 8ms. This Bandwidth is the default for NDOF Mode
bool anyMotion = true;    //To know which interrupt was triggered
bool updateThreshold = false;
int InterruptPin = 2; // Pin D2 is connected to the INT LED


void setup()
{
  // Initialize Serial Port
  Serial.begin(115200);
  Serial.println("Zoo Animal Interactive Decice");
  Serial.println("Created in 2022 as a University of Cincinnati Capstone Project");
  Serial.println("Built by Nate Alter and Ojas Anand");
  Serial.println("Git repo: https://github.com/N8DaGr84444/ZooAnimalInteractionDevice");
  Serial.println("-------------------------------------------------------------");
  Serial.println();
  Serial.println();

  // Setup 4 digit display
  const uint8_t D_FAC = getDFac();
  if (D_FAC > 500 || D_FAC < 10)
    initDFac();
  initEnc();
  initDisp();
  threshold = D_FAC;

  // Motion Sensor Initialization
  Wire.begin();    //Initialize I2C communication to the let the library communicate with the sensor.
  //Sensor Initialization
  Serial.println("Please wait. Initialization in process.");
  motionSensor.initSensor();              //The I2C Address can be changed here inside this function in the library
  motionSensor.setOperationMode(OPERATION_MODE_NDOF); //Can be configured to other operation modes as desired
  motionSensor.setUpdateMode(MANUAL);         //The default is AUTO. Changing to manual requires calling the relevant update functions prior to calling the read functions
  //Setting to MANUAL  requires lesser reads to the sensor
  
  attachInterrupt(digitalPinToInterrupt(InterruptPin), motionISR, RISING); //Attach the interrupt to the Interrupt Service Routine for a Rising Edge. Change the interrupt pin depending on the board

  //Setup the initial interrupt to trigger at No Motion
  motionSensor.resetInterrupt();
  motionSensor.enableSlowNoMotion(threshold, duration, NO_MOTION);
  anyMotion = false;
  motionSensor.accelInterrupts(ENABLE, ENABLE, ENABLE); //Accelerometer interrupts can be triggered from all 3 axes
  
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

  if (intDetected)
  {
    if (anyMotion)
    {
      Serial.println("You moved!! Try again. Keep the Device at one place.\n");
      intDetected = false;
      motionSensor.resetInterrupt();                   //Reset the interrupt line
      motionSensor.disableAnyMotion();                 //Disable the Any motion interrupt
      motionSensor.enableSlowNoMotion(threshold, duration, NO_MOTION); //Enable the No motion interrupt (can also use the Slow motion instead)
      anyMotion = false;
    }
    else
    {
      Serial.println("Device is not moving. You may start again.\n\n\n");
      Serial.println("Current threshold:");
      Serial.println(threshold);
      intDetected = false;
      motionSensor.resetInterrupt();             //Reset the interrupt line
      motionSensor.disableSlowNoMotion();          //Disable the Slow or No motion interrupt
      motionSensor.enableAnyMotion(threshold, duration); //Enable the Any motion interrupt
      anyMotion = true;
    }
  }

  if (updateThreshold)
  {
    motionSensor.resetInterrupt();                   //Reset the interrupt line
    motionSensor.disableAnyMotion();                 //Disable the Any motion interrupt
    motionSensor.enableAnyMotion(threshold, duration); //Enable the Any motion interrupt
    Serial.println("Threshold updated");
    updateThreshold = false;
  }
}

//Interrupt Service Routine when the sensor triggers an Interrupt
void motionISR()
{
  intDetected = true;
}

void setMotionThreshold(int cVal)
{
  uint8_t newThreshold = threshold + cVal;
  if (newThreshold >= 10 && newThreshold <= 500)
  {
    Serial.println("Changing threshold, keep device still");
    threshold = newThreshold;
//    intDetected = false;
//    motionSensor.resetInterrupt();                   //Reset the interrupt line
//    motionSensor.disableAnyMotion();                 //Disable the Any motion interrupt
//    motionSensor.enableSlowNoMotion(threshold, duration, NO_MOTION); //Enable the No motion interrupt (can also use the Slow motion instead)
//    anyMotion = false;
//    Serial.println("Current threshold:");
//    Serial.println(threshold);
//      intDetected = true;
    updateThreshold = true;
  }
}
