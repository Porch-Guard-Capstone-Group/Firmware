#include "Wire.h"
#include "SparkFun_MMA8452Q.h"    // Click here to get the library: http://librarymanager/All#SparkFun_MMA8452Q

const byte hx711_data_pin = A2;
const byte hx711_clock_pin = A3;
const int ledPin = 6;
const int buzzPin = 7;
const int trigPin = 8;
const int echoPin = 9;
bool firstILoop = true;
bool firstMLoop = true;
bool firstALoop = true;
float initialWeight = 0;
int initialDistance = 0;
int address = 0x1D;
float initialXValue = 0;
float initialYValue = 0;
float initialZValue = 0;
byte readValue = 0xFF;

#define idleState     0
#define monitorState  1
#define alarmState    2

int state = monitorState;

void setup();
void loop();
