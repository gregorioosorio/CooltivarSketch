// Cooltivar: is an IoT solution aimed to gather information and generate alerts based on them

#include "DHT.h"
#include <SoftwareSerial.h>
#include <BlynkSimpleSerial.h>
#include <SimpleTimer.h>

SoftwareSerial SwSerial(2, 3); // RX, TX
char auth[] = "044a7f4b43fa42f19ba577af3fb21918";
SimpleTimer timer;

#define DHTPIN 2     // what digital pin we're connected to

// Uncomment whatever type you're using!
#define DHTTYPE DHT11   // DHT 11
//#define DHTTYPE DHT22   // DHT 22  (AM2302), AM2321
//#define DHTTYPE DHT21   // DHT 21 (AM2301)

// Connect pin 1 (on the left) of the sensor to +5V
// NOTE: If using a board with 3.3V logic like an Arduino Due connect pin 1
// to 3.3V instead of 5V!
// Connect pin 2 of the sensor to whatever your DHTPIN is
// Connect pin 4 (on the right) of the sensor to GROUND
// Connect a 10K resistor from pin 2 (data) to pin 1 (power) of the sensor

// Initialize DHT sensor.
// Note that older versions of this library took an optional third parameter to
// tweak the timings for faster processors.  This parameter is no longer needed
// as the current DHT reading algorithm adjusts itself to work on faster procs.
DHT dht(DHTPIN, DHTTYPE);

void setup() {
  SwSerial.begin(9600);
  Blynk.begin(auth);
  timer.setInterval(4500, sendUptime);
  dht.begin();
}

void sendUptime()
{
  float t = dht.readTemperature();
  Blynk.virtualWrite(1, t);
}

void loop() {
  Blynk.run();
  timer.run();
}

