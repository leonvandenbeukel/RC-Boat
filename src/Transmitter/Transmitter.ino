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

Data_to_be_sent sent_data;
int offSignalSend = 0;

#define btnLeft 2
#define btnRight 3

void setup() {
  pinMode(btnLeft, INPUT_PULLUP);
  pinMode(btnRight, INPUT_PULLUP);

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

   if (valLeft == LOW && valRight == HIGH) {
    offSignalSend = 0;
    sent_data.ch1 = 1; 
    radio.write(&sent_data, sizeof(Data_to_be_sent));
  } else if (valRight == LOW && valLeft == HIGH) {
    offSignalSend = 0;
    sent_data.ch1 = 2;
    radio.write(&sent_data, sizeof(Data_to_be_sent));
  } else if (valRight == LOW && valLeft == LOW) {
    offSignalSend = 0;
    sent_data.ch1 = 3;
    radio.write(&sent_data, sizeof(Data_to_be_sent));
   } else {
      if (offSignalSend == 0) {
        sent_data.ch1 = 0;
        radio.write(&sent_data, sizeof(Data_to_be_sent));
        offSignalSend = 1;
      }
   }
  
   delay(20);
}
