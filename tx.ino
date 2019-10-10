#include <SPI.h>
#include <RF24.h>
#include <nRF24L01.h>

char* msg;
RF24 radio(9,10);
const uint64_t pipe=1;

void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
radio.begin();
radio.setPALevel(RF24_PA_MIN);
radio.openWritingPipe(pipe);
Serial.println("Opened !");

msg="Hello ! my name is Abel ";

}

void loop() {
  // put your main code here, to run repeatedly:
radio.write(msg,strlen(msg));
Serial.println("Written !");

delay(5000);
Serial.println("Wait...");
}
