
//"If you enjoyed this video, make sure to subscribe our channel ktronic for more!"

// Go to Sketch > Include Library > Manage Libraries....
// In the Library Manager, a window will pop up where you can search for libraries.
// Search for the library you need. For instance, search for "RF24" to install the RF24 library used for the NRF24L01 module.
// Select the library from the search results and click the Install button.
// Repeat the steps for any other libraries you need (e.g., "SPI" is usually pre-installed).
// Include necessary libraries

#include<SPI.h>
#include<nRF24L01.h>
#include<RF24.h>

// Define pins for the L298 motor driver
int ENA = 2;
int ENB = 7;
int MotorA1 = 3;
int MotorA2 = 4;
int MotorB1 = 5;
int MotorB2 = 6;

// Define CE and CSN pins for the NRF24L01
RF24 radio(8, 10);

const byte address[6] = "00001";

struct data {
  int xAxis;
  int yAxis;

};
data receive_data;



void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
radio.begin();
radio.openReadingPipe(0,address);
radio.setPALevel(RF24_PA_MIN);
radio.setDataRate(RF24_250KBPS);
radio.startListening();
pinMode(ENA, OUTPUT);
pinMode(ENB, OUTPUT);
pinMode(MotorA1, OUTPUT);
pinMode(MotorA2, OUTPUT);
pinMode(MotorB1, OUTPUT);
pinMode(MotorB2, OUTPUT);
}


void loop() {
  // put your main code here, to run repeatedly
 while(radio.available()) {
    radio.read(&receive_data, sizeof(data));
 if(receive_data.yAxis > 400) {
  digitalWrite(MotorA1, HIGH);
  digitalWrite(MotorA2, HIGH);
  digitalWrite(MotorB1, HIGH);
  digitalWrite(MotorB2, HIGH);
  analogWrite(ENA, 150);
  analogWrite(ENB, 150);
  
}else if(receive_data.yAxis < 320) {
  digitalWrite(MotorA1, LOW);
  digitalWrite(MotorA2, HIGH);
  digitalWrite(MotorB1, LOW);
  digitalWrite(MotorB2, HIGH);
  analogWrite(ENA, 150);
  analogWrite(ENB, 150);
} else if(receive_data.xAxis < 320){
  digitalWrite(MotorA1, HIGH);
  digitalWrite(MotorA2, LOW);
  digitalWrite(MotorB1, HIGH);
  digitalWrite(MotorB2, LOW);
  analogWrite(ENA, 150);
  analogWrite(ENB, 150);
}else if(receive_data.xAxis > 400){
  digitalWrite(MotorA1, HIGH);
  digitalWrite(MotorA2, LOW);
  digitalWrite(MotorB1, HIGH);
  digitalWrite(MotorB2, LOW);
  analogWrite(ENA, 150);
  analogWrite(ENB, 150);
}else {
  digitalWrite(MotorA1, LOW);
  digitalWrite(MotorA2, LOW);
  digitalWrite(MotorB1, LOW);
  digitalWrite(MotorB2, LOW);
  analogWrite(ENA, 0);
  analogWrite(ENB, 0);
  }
 }
}
