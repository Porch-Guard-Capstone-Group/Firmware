#include "ultrasonic.h"

int getDistance() {
  long duration = pulseIn(echoPin, HIGH);
  int distance = duration/29/2; //in cm
  return distance;
}
