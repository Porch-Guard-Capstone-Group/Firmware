#include "WiFiNINA.h"
#include "Firebase_Arduino_WiFiNINA.h"

#define FIREBASE_HOST "porchguard-default-rtdb.firebaseio.com" //datebase name linked to 
#define FIREBASE_AUTH "rwejMFn6v5ebSUF6obzcuNxMdZ8N4Bh6jkUaza6Y" //firebase authentication key
#define WIFI_SSID "TELUS2480-2.4G"
#define WIFI_PASS "kyu7mvz2q4"

void WiFiInit();
void FirebaseInit();
void sendState();
int recieveState();
