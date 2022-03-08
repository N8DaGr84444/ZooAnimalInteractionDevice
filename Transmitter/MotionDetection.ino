/**************************
 * Initialize and control motion shield
 */

// Libraries
#include "Arduino_NineAxesMotion.h"
#include <Wire.h>

NineAxesMotion motionSensor;   //Object for the sensor

void initMotionShield(void)
{
  bool intDetected = false;   //Flag to indicate if an interrupt was detected
  int threshold = 5;    //At a Range of 4g, the threshold is set at 39.05mg or 0.3830m/s2. This Range is the default for NDOF Mode
  int duration = 1;   //At a filter Bandwidth of 62.5Hz, the duration is 8ms. This Bandwidth is the default for NDOF Mode
  bool anyMotion = true;    //To know which interrupt was triggered 
}

void setupMotionShield(void)
{
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

 
