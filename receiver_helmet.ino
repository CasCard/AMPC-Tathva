#include <SPI.h>
#include <RF24.h>
#include <nRF24L01.h>

const int maxMsgLength=64;
char msg[maxMsgLength];

RF24 radio(7,8);
const uint64_t pipe=1;
void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
radio.begin();
radio.setPALevel(RF24_PA_MIN);
Serial.println("Started !");
radio.openReadingPipe(1,pipe);
Serial.println("Opened !");

radio.startListening();
Serial.println("Listening..");
}

void loop() {
  // put your main code here, to run repeatedly:
if(radio.available()){
  Serial.println("Available !");
  radio.read(msg,maxMsgLength - 1);
  Serial.println("Read: "+String(msg));
}else{
  Serial.println("Not Available");
}
delay(2500);
Serial.println("Wait...");
}
