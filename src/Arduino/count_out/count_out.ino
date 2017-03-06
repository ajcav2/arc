#include <Wire.h>
#include "Adafruit_VL6180X.h"

Adafruit_VL6180X vl = Adafruit_VL6180X();
int numberOut = 0;
boolean sensorBlocked = false;

void setup() {
  Serial.begin(115200);

  // wait for serial port to open on native usb devices
  while (!Serial) {
    delay(1);
  }
  
  if (! vl.begin()) {
    Serial.println("Failed to find sensor");
    while (1);
  }
}

void loop() {
  
  uint8_t range = vl.readRange();
  uint8_t status = vl.readRangeStatus();

// if the sensor was not previously blocked, increment counter 
// and sensorBlocked = true
  if (range < 50 && sensorBlocked == false) {
    numberOut++;
    sensorBlocked = true;
    Serial.println(numberOut);
  }

// if the sensor was blocked before, but now is reading a
// greater range, then sensor is now unblocked.  Onto the next
// arc-user.
  if (range >= 50 && sensorBlocked == true) {
    sensorBlocked = false;
  }

  
  delay(50);
}
