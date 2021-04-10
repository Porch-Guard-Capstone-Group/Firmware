#include "accelerometer.h"

MMA8452Q accel;                   // create instance of the MMA8452 class

void accelInit() {
  if (accel.begin() == false) {
    Serial.println("Not Connected. Please check connections and read the hookup guide.");
    while (1);
  }
}

void printXYZ() {
  if (accel.available()) {      // Wait for new data from accelerometer
  // Acceleration of x, y, and z directions in g units
  Serial.print("X: ");
  Serial.print(accel.getCalculatedX(), 3);
  Serial.print("\t");
  Serial.print("Y: ");
  Serial.print(accel.getCalculatedY(), 3);
  Serial.print("\t");
  Serial.print("Z: ");
  Serial.print(accel.getCalculatedZ(), 3);
  Serial.println();
  }
}

float getXValue() {
  if (accel.available()) {
    return accel.getCalculatedX();
  }
  else {
    return 98;
  }
}

float getYValue() {
   if (accel.available()) {
    return accel.getCalculatedY();
  }
  else {
    return 97;
  } 
}

float getZValue() {
   if (accel.available()) {
    return accel.getCalculatedZ();
  }
  else {
    return 96;
  } 
}
