/**************************
 * Initialize and control motion shield
 */

// Libraries
#include "Arduino_NineAxesMotion.h"
#include <Wire.h>

NineAxesMotion motionSensor;   //Object for the sensor
bool intDetected;
bool anyMotion;
int threshold;
int duration;

int InterruptPin = 2; // Pin D2 is connected to the INT LED

void initMotionShield(void)
{
  intDetected = false;   //Flag to indicate if an interrupt was detected
  threshold = 5;    //At a Range of 4g, the threshold is set at 39.05mg or 0.3830m/s2. This Range is the default for NDOF Mode
  duration = 1;   //At a filter Bandwidth of 62.5Hz, the duration is 8ms. This Bandwidth is the default for NDOF Mode
  anyMotion = true;    //To know which interrupt was triggered 
}

void setupMotionShield(void)
{
  // Initialize I2C communication for the motion sensor
  I2C.begin();

  // Attach interrupt to Interrupt Service Routine
  // for a Rising Edge. Change the interrupt pin depending on the board.
  attachInterrupt(digitalPinToInterrupt(InterruptPin), motionISR, RISING);
  
  // Initialize Sensor
  motionSensor.initSensor();
  motionSensor.setOperationMode(OPERATION_MODE_NDOF);
  motionSensor.setUpdateMode(MANUAL);

  // Set initial interrupt to trigger at No Motion
  motionSensor.resetInterrupt();
  motionSensor.enableSlowNoMotion(threshold, duration, NO_MOTION);
  anyMotion = false;

  // Enable accelerometer interrupts from all 3 axes
  motionSensor.accelInterrupts(ENABLE, ENABLE, ENABLE);
}

bool getIntDetected(void)
{
  return intDetected;
}

void setAnyMotion(bool AnyMotion)
{
  anyMotion = AnyMotion;
}

bool getAnyMotion(void)
{
  return anyMotion;
}

//Interrupt Service Routine when the sensor triggers an Interrupt
void motionISR(void)
{
//  Serial.println("Interrupt thrown");
//  intDetected = true;
//  intTriggered();
  if (anyMotion)
  {
    motionDetected();
  }
  else
  {
    motionStopped();
  }
}

//void intTriggered(void)
//{
//  if (intDetected)
//  {
//
//}

void motionDetected()
{
  Serial.println("You moved!! Try again. Keep the Device at one place.\n");
  intDetected = false;
  motionSensor.resetInterrupt();                   //Reset the interrupt line
  motionSensor.disableAnyMotion();                 //Disable the Any motion interrupt
  motionSensor.enableSlowNoMotion(threshold, duration, NO_MOTION); //Enable the No motion interrupt (can also use the Slow motion instead)
  anyMotion = false;
}

void motionStopped()
{
  Serial.println("Device is not moving. You may start again.\n\n\n");
  intDetected = false;
  motionSensor.resetInterrupt();             //Reset the interrupt line
  motionSensor.disableSlowNoMotion();          //Disable the Slow or No motion interrupt
  motionSensor.enableAnyMotion(threshold, duration); //Enable the Any motion interrupt
  anyMotion = true;
}
 
