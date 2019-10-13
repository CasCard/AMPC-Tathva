#include <SoftwareSerial.h>
float input_volt = 0.0; 
float temp=0.0;
float r1=10000.0;    //r1 value
float r2=100000.0;      //r2 value

   
void setup()
{
   Serial.begin(9600);     //  opens serial port, sets data rate to 9600 bps
}

void loop()
{
    int analogvalue = analogRead(A0);
    temp = (analogvalue * 5.0) / 1024.0;       // FORMULA USED TO CONVERT THE VOLTAGE
    input_volt =( temp / (r2/(r1+r2)))*100;    // actual value of the form 0.01,so multiplied with 100
  if (input_volt <1) //threshold voltage
     {
       input_volt=0.0;
     } 
    Serial.print("v= ");                 // prints the voltage value in the serial monitor
    Serial.println(input_volt );
    delay(300);
}
