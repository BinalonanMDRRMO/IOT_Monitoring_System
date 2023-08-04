#define BLYNK_PRINT Serial  // Defining serial for BLYNK APP
#define BLYNK_TEMPLATE_ID "TMPL61Yb9x_Fq" //Template ID from Blynk Website
#define BLYNK_TEMPLATE_NAME "MDRRMO Binalonan" //Template Name from Blynk Website
 
#include <ESP8266WiFi.h>         // Library for wifi module
#include <BlynkSimpleEsp8266.h>  // Library of Blynk App
#include <HCSR04.h>              // Library of Ultrasonic Sensor
#include <DHT.h>                 // Library of Temp and Hum Sensor
#include <SimpleTimer.h>         // Library of the timer for the data to be sent on Blynk app

// ultrasonic sensor
#define trig D6  // Setting the name of D6 Pin as trig, trig Pin to D6
#define echo D5  // Setting the name of D5 Pin as echo, echo Pin to D5

// Temp and Humid Sensor
#define DHTPIN 2       // Setting the name of D4 Pin as DHTPIN, out Pin to D4
#define DHTTYPE DHT22  // setting name of DHT22

DHT dht(DHTPIN, DHTTYPE);  // Defining DHT
HCSR04 hc(trig, echo);     // Defining HCSR04

BlynkTimer timer;

long distancecm = 50;       // change this whatever the distance from the ground to ultrasonic in CM
long distancepercent = 50;  // change this whatever the distance from the ground to ultrasonic in CM


char auth[] = "ZgbawEbNxkMNi7XW56pWwJ7vuPm7AGcs";  //your auth from Blynk
char ssid[] = "PLDTHOMEFIBR4HvMs";                 // your ssid
char pass[] = "PLDTWIFIhrrJD";                     // your pass


// code for Centimeter
void waterLevelcm() {
  digitalWrite(trig, LOW);
  delayMicroseconds(1);
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);
  long t = pulseIn(echo, HIGH);
  long cm = t / 29 / 2;
  Serial.println(cm);
  double level = distancecm - cm;
  if (level > 0) {
    long centimeter = ((level / distancecm)) * 50;  //  change this whatever the  the value set in distancecm on Line 24
    Blynk.virtualWrite(V0, centimeter);
  } else {
    Blynk.virtualWrite(V0, 0);  //V0 is for centimeter //Virtual Pin set in BLYNK app
  }
}



// code for Percentage
void waterLevelpercent() {
  digitalWrite(trig, LOW);
  delayMicroseconds(1);
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);
  long t = pulseIn(echo, HIGH);
  long cm = t / 29 / 2;
  Serial.println(cm);
  double level = distancepercent - cm;
  if (level > 0) {
    long percentage = ((level / distancepercent)) * 100;  // leave as it is because we are getting the percentage of the reading
    Blynk.virtualWrite(V1, percentage);
  } else {
    Blynk.virtualWrite(V1, 0);  //V1 is for percentage //Virtual Pin set in BLYNK app
  }
}


// code for Humidity and Temperature Sensor
void sendSensor() {
  float h = dht.readHumidity();     // code to read the Humidity
  float t = dht.readTemperature();  // code to read the Temperature

  if (isnan(h) || isnan(t)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  Blynk.virtualWrite(V5, h);  //V5 is for Humidity //Virtual Pin set in BLYNK app
  Blynk.virtualWrite(V6, t);  //V6 is for Temperature //Virtual Pin set in BLYNK app
}


void setup() {
  pinMode(trig, OUTPUT);  // setting trig pin as OUTPUT
  pinMode(echo, INPUT);   // setting echo pin as INPUT

  // Initialize the Serial Monitor
  // Setting the baud rate of Serial Monitor (Arduino)
  Serial.begin(9600);
  delay(100);

  //Setting the Connection to BLYNK app
  Blynk.begin(auth, ssid, pass);
  timer.setInterval(10L, waterLevelcm); // every 10 millisecond interval
  timer.setInterval(10L, waterLevelpercent); // every 10 millisecond interval
  timer.setInterval(1000L, sendSensor); // every 1 second interval
  dht.begin();  // temp and humidity sensor
}


void loop() {
  Blynk.run();
  timer.run();
}
