
#include <NTPClient.h>
#include <ESP8266WiFi.h>
#include <WiFiUdp.h>

const char *ssid     = "ssid name";
const char *password = "pass";

const long utcOffsetInSeconds = -14400;

char daysOfTheWeek[7][12] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};

// Define NTP Client to get time
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "pool.ntp.org", utcOffsetInSeconds);

const int relayPin = 5;

bool hasActivatedRelay = false;

void setup() {
  Serial.begin(115200);
  pinMode(relayPin, OUTPUT);

  WiFi.begin(ssid, password);

  while ( WiFi.status() != WL_CONNECTED ) {
    delay ( 500 );
    Serial.print ( "." );
  }
  Serial.println("Connected to Wi-Fi");

  timeClient.begin();
}

void loop() {
  timeClient.update();

  Serial.print(daysOfTheWeek[timeClient.getDay()]);
  Serial.print(", ");
  Serial.print(timeClient.getHours());
  Serial.print(":");
  Serial.print(timeClient.getMinutes());
  Serial.print(":");
  Serial.println(timeClient.getSeconds());
  //Serial.println(timeClient.getFormattedTime());

  // Change the below getminute value to the minute it should sync, 
  // based on what position the clock minute hand is when the solenoid is activated
  if (timeClient.getMinutes() == 59) {
    if (!hasActivatedRelay) {
      digitalWrite(relayPin, HIGH);
      // Below, set the time for the solenoid to be active each hour, in milliseconds
      delay(500);
      digitalWrite(relayPin, LOW);
      hasActivatedRelay = true;
    }
  } else {
    hasActivatedRelay = false;
  }

  delay(1000);
}
