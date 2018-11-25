// Receiver

#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

#define Ain1 3
#define Ain2 4
#define Bin1 5
#define Bin2 6

const uint64_t pipeIn = 0xE8E8F0F0E1LL;    
RF24 radio(9, 10);  //CSN and CE pins

// Should not exceed 32 bytes
struct Received_data {
  byte ch1;
};

Received_data received_data;

void setup() {

  Serial.begin(9600);
  
  pinMode(Ain1, OUTPUT);  //Ain1
  pinMode(Ain2, OUTPUT);  //Ain2
  pinMode(Bin1, OUTPUT);  //Bin1
  pinMode(Bin2, OUTPUT);  //Bin2
  
  received_data.ch1 = 0;
  radio.begin();
  //radio.setPALevel(RF24_PA_LOW);
  radio.setAutoAck(false);
  radio.setDataRate(RF24_250KBPS);  
  radio.openReadingPipe(1,pipeIn);
  radio.startListening();
}

void loop() {

  if (radio.available()) 
    radio.read(&received_data, sizeof(Received_data));
 
  int ch1_value = received_data.ch1;  

  if (ch1_value >= 0 && ch1_value <= 6) {
    if (ch1_value != 0)
      Serial.println(ch1_value);
   
    if (ch1_value == 1) {   
      // Left forward         
      digitalWrite(Ain1,HIGH);
      digitalWrite(Ain2,LOW);
      digitalWrite(Bin1,LOW);
      digitalWrite(Bin2,LOW);
    } else if (ch1_value == 2) {
      // Right forward
      digitalWrite(Ain1,LOW);
      digitalWrite(Ain2,LOW);
      digitalWrite(Bin1,HIGH);
      digitalWrite(Bin2,LOW);
    } else if (ch1_value == 3) {
      // Both forward
      digitalWrite(Ain1,HIGH);
      digitalWrite(Ain2,LOW);
      digitalWrite(Bin1,HIGH);
      digitalWrite(Bin2,LOW);
    } else if (ch1_value == 4) {
      // Left backwards
      digitalWrite(Ain1,LOW);
      digitalWrite(Ain2,HIGH);
      digitalWrite(Bin1,LOW);
      digitalWrite(Bin2,LOW);
    } else if (ch1_value == 5) {
      // Right backwards
      digitalWrite(Ain1,LOW);
      digitalWrite(Ain2,LOW);
      digitalWrite(Bin1,LOW);
      digitalWrite(Bin2,HIGH);
    } else if (ch1_value == 6) {
      // Both backwards
      digitalWrite(Ain1,LOW);
      digitalWrite(Ain2,HIGH);
      digitalWrite(Bin1,LOW);
      digitalWrite(Bin2,HIGH);
    } else {
      // Both off
      digitalWrite(Ain1,LOW);
      digitalWrite(Ain2,LOW);
      digitalWrite(Bin1,LOW);
      digitalWrite(Bin2,LOW); 
    }       
  }
}
