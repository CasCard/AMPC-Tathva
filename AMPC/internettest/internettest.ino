#include <TinyGPS.h>
#include <SoftwareSerial.h>
SoftwareSerial mySerial(9, 10);

void setup()
{
  mySerial.begin(9600);   // Setting the baud rate of GSM Module  
  Serial.begin(9600);    // Setting the baud rate of Serial Monitor (Arduino)
  delay(100);
}


void loop()
{
  if (Serial.available()>0)
   switch(Serial.read())
  {
    case 's':
      SendMessage();
      break;
    case 'r':
      RecieveMessage();
      break;
  }

 if (mySerial.available()>0)
   Serial.write(mySerial.read());
}


 void SendMessage()
{
  // HTTP Requests  

  mySerial.println("AT+SAPBR=3,1,\"CONTYPE\",\"GPRS\"");
  delay(2000);
  //NSP Settings
  mySerial.println("AT+SAPBR=3,1,\"APN\",\"idea\"");
  delay(2000);
  mySerial.println("AT+SAPBR=1,1");
  delay(2000);
  mySerial.println("AT+HTTPINIT");
  delay(2000); 
mySerial.println("AT+HTTPPARA=\"URL\",\"http://datathon.ml/write.php?lat=11.24&lon=74.14&lin=google\""); 
    delay(8000);
    mySerial.println("AT+HTTPACTION=0");
    delay(7000);
//    // read server response
//    mySerial.println("AT+HTTPREAD"); 
//    delay(2000);
//    mySerial.println("");
//    mySerial.println("AT+HTTPTERM");
//    delay(1000);
//    mySerial.println("");
//    delay(10000);
//    mySerial.println("AT+HTTPPARA=\"URL\",\"http://datathon.ml/write.php?lat=11.24&lon=74.14&lin=google\""); 
//    delay(5000);
    Serial.println("AT+HTTPACTION=0");
    delay(6000);
    Serial.println("Server Upload Successful");
}


 void RecieveMessage()
{
  mySerial.println("AT+CNMI=2,2,0,0,0"); // AT Command to receive a live SMS
  delay(1000);
 }
