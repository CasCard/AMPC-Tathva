#include<SoftwareSerial.h>
SoftwareSerial GPRS(9,10);
void setup() {
  // put your setup code here, to run once:
GPRS.begin(9600);
Serial.begin(9600);

}

void loop() {
  // put your main code here, to run repeatedly:
while(GPRS.available())
  Serial.write(GPRS.read());

while(Serial.available())
  GPRS.write(Serial.read());
}
