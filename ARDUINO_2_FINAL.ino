#include <SoftwareSerial.h> // software serial library

// Define the pins of SIM900A module
#define sim900aSerialRX 9
#define sim900aSerialTX 10

// Defining SofrwareSerial
SoftwareSerial sim900aSerial(sim900aSerialRX, sim900aSerialTX);

// Define the pin for the buzzer
#define buzzerPin 4

void setup() {
  // Initialize the SIM900A module
  // Setting the baud rate of GSM Module
  sim900aSerial.begin(9600);
  
  // Initialize the Serial Monitor
  // Setting the baud rate of Serial Monitor (Arduino)
  Serial.begin(115200);
  delay(1000);

  // Setting the GSM Module to Text Mode
  sim900aSerial.println("AT+CNMI=2,2,0,0,0");
  delay(1000);

  // Setting the GSM Module to Receive SMS
  sim900aSerial.println("AT+CMGF=1");
  delay(1000);

  // Setting Pin 4 as an Output
  pinMode(buzzerPin, OUTPUT);
}

void loop() {
  // Check if there is an incoming SMS message
  if (sim900aSerial.available() > 0) {
    String message = sim900aSerial.readString();

    // Check if the message contains the keyword "BUZZER"
    if (message.indexOf("alert") >= 0) {
       Serial.println("Buzzer On");
      digitalWrite(buzzerPin, HIGH);  // Turn on the buzzer
      delay(1000);
      digitalWrite(buzzerPin, LOW);  // Turn off the buzzer
      delay(1000);
      digitalWrite(buzzerPin, HIGH);  // Turn on the buzzer
      delay(1000);
      digitalWrite(buzzerPin, LOW);  // Turn off the buzzer
      delay(1000);
      digitalWrite(buzzerPin, HIGH);  // Turn on the buzzer
      delay(1000);
      digitalWrite(buzzerPin, LOW);  // Turn off the buzzer
      delay(1000);
      digitalWrite(buzzerPin, HIGH);  // Turn on the buzzer
      delay(1000);
      digitalWrite(buzzerPin, LOW);  // Turn off the buzzer
      delay(1000);
      digitalWrite(buzzerPin, HIGH);  // Turn on the buzzer
      delay(1000);
      digitalWrite(buzzerPin, LOW);  // Turn off the buzzer
      delay(1000);
      Serial.println("Buzzer Off");
    }
    //code for sending SMS to Residents
    // the sender will be MDDRMO Official
    if (message.indexOf("sms") >= 0) {
      Serial.println("Sending SMS to Residents...........");
      sim900aSerial.println("AT+CMGF=1");                    //Sets the GSM Module in Text Mode
      delay(1000);                                      // Delay of 1000 milli seconds or 1 second
      sim900aSerial.println("AT+CMGS=\"+639303061829\"\r");  // Replace x with your mobile number(not the number which insert in to gsm module)
      delay(1000);
      sim900aSerial.println("MAGSILIKAS NA");
      delay(100);
      Serial.println("Succesfully sent..");
      
      sim900aSerial.println((char)26);  // ASCII code of CTRL+Z
      delay(100);
    }
  }
}