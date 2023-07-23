#include <SoftwareSerial.h>  // software serial library

// Define the pins of SIM900A module
#define sim900aSerialRX 9
#define sim900aSerialTX 10

// Defining SofrwareSerial
SoftwareSerial sim900aSerial(sim900aSerialRX, sim900aSerialTX);

// Define the pins of water level sensor
#define sensorPower 7
#define sensorPin A0


// Value for storing water level
int val = 0;

void setup() {
  // Initialize the SIM900A module
  // Setting the baud rate of GSM Module
  sim900aSerial.begin(9600);
  
  // Initialize the Serial Monitor
  // Setting the baud rate of Serial Monitor (Arduino)
  Serial.begin(9600);      


  // Setting Pin 7 as an OUTPUT
  pinMode(sensorPower, OUTPUT);

  // Setting Pin A0 to LOW so no power flows through the sensor
  digitalWrite(sensorPower, LOW);
}

//This is a function used to get the reading
int readSensor() {
  digitalWrite(sensorPower, HIGH);  // Turn the sensor ON
  delay(10);                        // wait 10 milliseconds
  val = analogRead(sensorPin);      // Read the analog value form sensor
  digitalWrite(sensorPower, LOW);   // Turn the sensor OFF
  return val;                       // send current reading
}

void loop() {
  //get the reading from the function and print it
  int level = readSensor();

  Serial.print("Water level: ");
  Serial.println(level);

  if (level < 300) {

    Serial.println("no flood detected");
    Serial.println("----------------------------------------------");
    delay(1000);

  } else {

    Serial.println("flood detected");
    Serial.println("Sending SMS to MDRRMO Official..........");
    Serial.println("Sending SMS to trigger the Buzzer..........");
    Serial.println("----------------------------------------------");

    // code for sending SMS
    //code for sending sms to mdrrmo official
    sim900aSerial.println("AT+CMGF=1");  //Sets the GSM Module in Text Mode
    delay(1000);                   // Delay of 1000 milli seconds or 1 second
    sim900aSerial.println("AT+CMGS=\"+639157652349\"\r");
    delay(1000);
    sim900aSerial.println("Flood Detected!");
    delay(100);
    Serial.println("Succesfully sent..");
    sim900aSerial.println((char)26);  // ASCII code of CTRL+Z
    delay(1000);

    // code for sending SMS
    //code for sending sms to triger the buzzer
    sim900aSerial.println("AT+CMGF=1");  //Sets the GSM Module in Text Mode
    delay(1000);                   // Delay of 1000 milli seconds or 1 second
    sim900aSerial.println("AT+CMGS=\"+639510501046\"\r");
    delay(1000);
    sim900aSerial.println("alert");
    delay(100);
    Serial.println("Succesfully sent..");
    sim900aSerial.println((char)26);  // ASCII code of CTRL+Z
    delay(1000);
  }
}
