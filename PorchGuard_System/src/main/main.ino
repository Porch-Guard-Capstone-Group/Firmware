#include "main.h"
#include "accelerometer.h"
#include "loadcell.h"
#include "proximity.h"
#include "ultrasonic.h"
#include "firebase.h"

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  WiFiInit();
  FirebaseInit();
  accelInit();
  //loadcellInit();
  sendState(); // update database with default state value (idleState)
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  switch (state) {
    case idleState:
    printXYZ();
    if (firstILoop) {
      initialXValue = getXValue();
      Serial.print("initial X: ");
      Serial.println(initialXValue);
      initialYValue = getYValue();
      Serial.print("initial Y: ");
      Serial.println(initialYValue);
      initialZValue = getZValue();
      Serial.print("initial Z: ");
      Serial.println(initialZValue);
      firstILoop = false;
    }
    else {
      if (getXValue() < initialXValue-0.5 || getXValue() > initialXValue+0.5) {
        state = alarmState;
        Serial.println(state);
        sendState();
      }
      else if (getYValue() < initialYValue-0.5 || getYValue() > initialYValue+0.5) {
        state = alarmState;
        Serial.println(state);
        sendState();
      }
      else if (getZValue() < initialZValue-1 || getZValue() > initialZValue+1) {
        state = alarmState;
        Serial.println(state);
        sendState();
      }
    }
    /*
    // load cell waits for significant change in weight for sufficient time
    if(loadcellDetect() > 5) {
      initialWeight = loadcellDetect();
      state = monitorState;
      Serial.println(state);
      sendState();
    }
    */
    break;

    case monitorState:
    int tempDistance;
    if(firstMLoop) {
      initialDistance = getDistance();
      Serial.print("Initial Distance: ");
      Serial.println(initialDistance);
      firstMLoop = false;
    }
    else {
    tempDistance = getDistance();
    Serial.print("Distance: ");
    Serial.println(tempDistance);
      if ((tempDistance > (initialDistance+3)) || (tempDistance < (initialDistance-3))) {
        state = alarmState;
        Serial.print("Difference of ");
        Serial.print(tempDistance - initialDistance);
        Serial.println(" detected. Going into alarm state.");
        sendState();
      }
      else {
          Serial.println("Package Secure");
      }
    }
    /*
    if (loadcellDetect() > 1.1*initialWeight) {
      initialWeight = loadcellDetect();
    }
    else if (loadcellDetect() < .9*initialWeight) {
      state = alarmState;
      Serial.println(state);
      sendState();
    }
    */

    // TODO: prox sensor watches for movement in front of it
    // change state if prompted by database
    /*
    state = recieveState();
    if (state != monitorState) {
      Serial.println(state);
      sendState();
    }*/
    break;

    case alarmState:
    // trigger alarm: LED and Piezobuzzer in loop
    digitalWrite(ledPin, HIGH);
    tone(buzzPin, 2000);
    Serial.print("ALARM!\n");
    Serial.print("Distance: ");
    Serial.print(getDistance());
    Serial.println(" cm");
    delay(100);
    digitalWrite(ledPin, LOW);
    tone(buzzPin,500);
    delay(100);
    // wait to recieve state update from database
    state = recieveState();
    if (state != alarmState) {
      Serial.println(state);
      digitalWrite(ledPin, LOW);
      tone(buzzPin, 0);
      firstILoop = true;
      firstMLoop = true;
      sendState();
    }
    break;
  }
}
