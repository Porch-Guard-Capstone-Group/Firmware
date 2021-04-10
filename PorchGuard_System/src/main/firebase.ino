#include "firebase.h"

FirebaseData firebaseData;
String path = "/status";
String jsonStr;

void WiFiInit() {
  Serial.println("Connecting to WiFi");
  int status = WL_IDLE_STATUS;
  while(status != WL_CONNECTED) {
    status = WiFi.begin(WIFI_SSID, WIFI_PASS);
    Serial.print(".");
    delay(300);
  }
  Serial.print("Connected to WiFi IP: ");
  Serial.println(WiFi.localIP());
}

void FirebaseInit() {
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH, WIFI_SSID, WIFI_PASS);
  Firebase.reconnectWiFi(true);
  Wire.begin();
  pinMode(ledPin, OUTPUT);
  pinMode(buzzPin, OUTPUT);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  Wire.beginTransmission(address);
  Wire.write(0x0D); //set pointer to register
  Wire.requestFrom(address, 1); //request 1 byte from register
  readValue = Wire.read();
  Wire.endTransmission();
}

void sendState() {
  if (Firebase.setInt(firebaseData, path + "/state", state)) {
    Serial.println("----------Set State-----------");
    Serial.println("PATH: " + firebaseData.dataPath());
    Serial.println("TYPE: " + firebaseData.dataType());
    Serial.print("VALUE: ");
    if (firebaseData.dataType() == "int")
      Serial.println(firebaseData.intData());
    else if (firebaseData.dataType() == "float")
      Serial.println(firebaseData.floatData());
    else if (firebaseData.dataType() == "boolean")
      Serial.println(firebaseData.boolData() == 1 ? "true" : "false");
    else if (firebaseData.dataType() == "string")
      Serial.println(firebaseData.stringData());
    else if (firebaseData.dataType() == "json")
      Serial.println(firebaseData.jsonData());
    Serial.println("--------------------------------");
    Serial.println();
  }
  else {
    Serial.println("----------Can't set data--------");
    Serial.println("REASON: " + firebaseData.errorReason());
    Serial.println("--------------------------------");
    Serial.println();
  }
}

int recieveState() {
   if (Firebase.getInt(firebaseData, path + "/state")) {
    Serial.println("----------Get State-----------");
    Serial.println("PATH: " + firebaseData.dataPath());
    Serial.println("TYPE: " + firebaseData.dataType());
    Serial.print("VALUE: ");
    if (firebaseData.dataType() == "int")
      Serial.println(firebaseData.intData());
    else if (firebaseData.dataType() == "float")
      Serial.println(firebaseData.floatData());
    else if (firebaseData.dataType() == "boolean")
      Serial.println(firebaseData.boolData() == 1 ? "true" : "false");
    else if (firebaseData.dataType() == "string")
      Serial.println(firebaseData.stringData());
    else if (firebaseData.dataType() == "json")
      Serial.println(firebaseData.jsonData());
    Serial.println("--------------------------------");
    Serial.println();
    return firebaseData.intData();
  }
  else {
    Serial.println("----------Can't get data--------");
    Serial.println("REASON: " + firebaseData.errorReason());
    Serial.println("--------------------------------");
    Serial.println();
    return 99; //error code
  }
}
