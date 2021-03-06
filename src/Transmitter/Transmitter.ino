// Transmitter

#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

const uint64_t my_radio_pipe = 0xE8E8F0F0E1LL; 
RF24 radio(9, 10);

// Should not exceed 32 bytes
struct Data_to_be_sent {
  byte ch1; 
};

volatile Data_to_be_sent sent_data;
volatile int offSignalSend = 0;

#define btnLeft 2
#define btnRight 3
#define btnLeftDown 4
#define btnRightDown 5

#define sendLED 6

void setup() {
  pinMode(btnLeft, INPUT_PULLUP);
  pinMode(btnRight, INPUT_PULLUP);
  pinMode(btnLeftDown, INPUT_PULLUP);
  pinMode(btnRightDown, INPUT_PULLUP);

  pinMode(sendLED, OUTPUT);
  //Serial.begin(9600);

  radio.begin();
  radio.setAutoAck(false);
  radio.setDataRate(RF24_250KBPS);
  radio.openWritingPipe(my_radio_pipe);  
  sent_data.ch1 = 0;
}

void loop() {

   int valLeft = digitalRead(btnLeft);
   int valRight = digitalRead(btnRight);
   int valLeftDown = digitalRead(btnLeftDown);
   int valRightDown = digitalRead(btnRightDown);

   digitalWrite(sendLED, LOW);

   if (valLeft == LOW && valRight == HIGH) {
    // Left forward
    offSignalSend = 0;
    sent_data.ch1 = 1; 
    digitalWrite(sendLED, HIGH);    
    radio.write(&sent_data, sizeof(Data_to_be_sent));
  } else if (valRight == LOW && valLeft == HIGH) {
    // Right forward
    offSignalSend = 0;
    sent_data.ch1 = 2;
    digitalWrite(sendLED, HIGH);    
    radio.write(&sent_data, sizeof(Data_to_be_sent));
  } else if (valRight == LOW && valLeft == LOW) {
    // Both forward
    offSignalSend = 0;
    sent_data.ch1 = 3;
    digitalWrite(sendLED, HIGH);    
    radio.write(&sent_data, sizeof(Data_to_be_sent));
  } else if (valRightDown == LOW && valLeftDown == HIGH) {
    // Left backwards
    offSignalSend = 0;
    sent_data.ch1 = 4;
    digitalWrite(sendLED, HIGH);    
    radio.write(&sent_data, sizeof(Data_to_be_sent));
  } else if (valRightDown == HIGH && valLeftDown == LOW) {
    // Right backwards
    offSignalSend = 0;
    sent_data.ch1 = 5;
    digitalWrite(sendLED, HIGH);    
    radio.write(&sent_data, sizeof(Data_to_be_sent));
  } else if (valRightDown == LOW && valLeftDown == LOW) {
    // Both backwards
    offSignalSend = 0;
    sent_data.ch1 = 6;
    digitalWrite(sendLED, HIGH);    
    radio.write(&sent_data, sizeof(Data_to_be_sent));
   } else {
      if (offSignalSend == 0) {
        for (int i=0; i<10; i++) {
          sent_data.ch1 = 0;
          digitalWrite(sendLED, HIGH);    
          radio.write(&sent_data, sizeof(Data_to_be_sent));
          offSignalSend = 1;
        }
      }
   }
  
   //delay(20);
}
