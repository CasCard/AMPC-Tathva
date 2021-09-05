#include <SoftwareSerial.h>
#include <nRF24L01.h>
#include <printf.h>
#include <RF24.h>
#include <RF24_config.h>
#include <SPI.h>
#include <Wire.h>

float input_volt = 0; 
float temp=0.0;
float r1=10000.0;    //r1 value
float r2=100000.0;      //r2 value

RF24 radio(7,8);
const byte address[6]="00001";

struct Data_Package {
  float voltage;
};
Data_Package data;

void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
  radio.begin();
  radio.openWritingPipe(address);
  radio.setAutoAck(false);
  radio.setDataRate(RF24_250KBPS);
  radio.setPALevel(RF24_PA_LOW);

//msg="Hello ! my name is Abel ";
  data.voltage=0.0;
}

void loop() {
  // put your main code here, to run repeatedly:
//  data.voltage=map(analogRead(A0),0,1023,0,255);
//  radio.write(&data, sizeof(Data_Package));
//  Serial.println(data.voltage);
//  delay(300);
int analogvalue = analogRead(A0);
    temp = (analogvalue * 5.0) / 1024.0;       // FORMULA USED TO CONVERT THE VOLTAGE
    data.voltage =(temp / (r2/(r1+r2)))*100;    // actual value of the form 0.01,so multiplied with 100




if (data.voltage <1) //threshold voltage
   {
     data.voltage=0.0;
   } 
    Serial.print("v= ");                 // prints the voltage value in the serial monitor
    Serial.println(data.voltage);
    radio.write(&data,sizeof(Data_Package));
    Serial.println("Written !");
    delay(1000);


 
}
 

 
