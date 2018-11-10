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

int ch1_value = 0;
unsigned long last_Time = 0;
Received_data received_data;

void setup() {
  
  pinMode(Ain1, OUTPUT);  //Ain1
  pinMode(Ain2, OUTPUT);  //Ain2
  pinMode(Bin1, OUTPUT);  //Bin1
  pinMode(Bin2, OUTPUT);  //Bin2

  Serial.begin(9600);

  received_data.ch1 = 0;
  radio.begin();
  radio.setAutoAck(false);
  radio.setDataRate(RF24_250KBPS);  
  radio.openReadingPipe(1,pipeIn);
  radio.startListening();

}

void receive_the_data()
  {
    while ( radio.available() ) {
    radio.read(&received_data, sizeof(Received_data));
    last_Time = millis(); 
  }
}

void loop() {

  receive_the_data();  
  ch1_value = received_data.ch1;// map(received_data.ch1,0,255,1000,2000);
  Serial.println(ch1_value);

  if (ch1_value == 1) {
    digitalWrite(Ain1,HIGH);
    digitalWrite(Ain2,LOW);
    digitalWrite(Bin1,LOW);
    digitalWrite(Bin2,LOW);
  }else if (ch1_value ==2) {
    digitalWrite(Ain1,LOW);
    digitalWrite(Ain2,LOW);
    digitalWrite(Bin1,HIGH);
    digitalWrite(Bin2,LOW);
  }else if (ch1_value ==3) {
    digitalWrite(Ain1,HIGH);
    digitalWrite(Ain2,LOW);
    digitalWrite(Bin1,HIGH);
    digitalWrite(Bin2,LOW);
  }else {
    digitalWrite(Ain1,LOW);
    digitalWrite(Ain2,LOW);
    digitalWrite(Bin1,LOW);
    digitalWrite(Bin2,LOW);
    Serial.print("both off");
  }
  
}
