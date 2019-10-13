 #include <TinyGPS.h>
#include <SoftwareSerial.h>
#include <LiquidCrystal.h>   
unsigned long fix_age;
SoftwareSerial GPS(4,3);
TinyGPS gps;
void gpsdump(TinyGPS &gps);
bool feedgps();
void getGPS();
long lat, lon; 
double LAT, LON;
 void setup1()
 {
  GPS.begin(9600);
  Serial.begin(9600);
  getGPS();
  Serial.print("Latitude : ");
  Serial.print(LAT/1000000,12);
  Serial.print(" :: Longitude : ");
  Serial.println(LON/1000000,12);
}
 void loop1()
 {
  long lat, lon;
  unsigned long fix_age, time, date, speed, course;
  unsigned long chars;
  unsigned short sentences, failed_checksum;
  // retrieves +/- lat/long in 100000ths of a degree
  gps.get_position(&lat, &lon, &fix_age);
  // time in hh:mm:ss, date in dd/mm/yy
/*gps.get_datetime(&date, &time, &fix_age);
  year = date % 100;
  month = (date / 100) % 100;
  day = date / 10000;
  hour = time / 1000000;
  minute =  (time / 10000) % 100;
  second = (time / 100) % 100;
  Serial.print("Date: ");
  Serial.print(year); Serial.print("/");
  Serial.print(month); Serial.print("/");
  Serial.print(day);
  Serial.print(" :: Time: ");
  Serial.print(hour); Serial.print(":");
  Serial.print(minute); Serial.print(":");
  Serial.println(second);
*/
  
}
void getGPS(){
  bool newdata = false;
  unsigned long start = millis();
  // Every 1 seconds we print an update
  while (millis() - start < 1000)
  {
    if (feedgps ()){
      newdata = true;
    }
  }
  if (newdata)
  {
    gpsdump(gps);
  }
}
bool feedgps(){
  while (GPS.available())
  {
    if (gps.encode(GPS.read()))
      return true;
  }
  return 0;
}
  void gpsdump(TinyGPS &gps)
{
  //byte month, day, hour, minute, second, hundredths;
  gps.get_position(&lat, &lon);
  LAT = lat;
  LON = lon;
  {
    feedgps(); // If we don't feed the gps during this long 
//routine, we may drop characters and get checksum errors
  }
  }
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
{float volage;
  mySerial.println("AT+CMGF=1");    //Sets the GSM Module in Text Mode
  delay(1000);  // Delay of 1000 milli seconds or 1 second
  mySerial.println("AT+CMGS=\"+919895935513\"\r"); // Replace x with mobile number
  delay(1000);
  GPS.begin(9600);
  Serial.begin(9600);
  getGPS();
 //https://www.google.com/maps/dir/'10.462682,76.040111'/'11.32074546,75.93459320'/ 
  String buf;
     buf += F("http://maps.google.com/maps?saddr=My%20location&daddr=");
     buf += String(LAT/1000000,12);
     buf += F(",");
     buf += String(LON/1000000,12);
     buf +=F("&mode=driving");
     mySerial.print("Latitude =");
     mySerial.println(LAT/1000000,12);
     Serial.println(LAT/1000000,12);
     mySerial.print("longitude =");
     mySerial.println( LON/1000000 ,12);
     Serial.println(LON/1000000,12);
    
     mySerial.println(buf);
    loop2();
  
     
   // The SMS text you want to send
  delay(100);
  
   mySerial.println((char)26);// ASCII code of CTRL+Z
  delay(1000);
}


 void RecieveMessage()
{
  mySerial.println("AT+CNMI=2,2,0,0,0"); // AT Command to receive a live SMS
  delay(1000);
 }

 

   // LIBRARY TO ACCESS THE LCD DISPLAY
LiquidCrystal lcd( 4, 5, 6, 7,8 ,9 );
float input_volt = 0.0; 
float temp=0.0;
float r1=10000.0;    //r1 value
float r2=100000.0;      //r2 value

   
void setup2()
{
   Serial.begin(9600);     //  opens serial port, sets data rate to 9600 bps
   lcd.begin(16, 2);       //// set up the LCD's number of columns and rows
   lcd.print("DC DIGI VOLTMETER");
}

void loop2()
{
    int analogvalue = analogRead(A0);
    temp = (analogvalue * 5.0) / 1024.0;       // FORMULA USED TO CONVERT THE VOLTAGE
    input_volt =( temp / (r2/(r1+r2)))*100;    // actual value of the form 0.01,so multiplied with 100
if (input_volt <1) //threshold voltage
   {
     input_volt=0.0;
   } 
   mySerial.print("v= "); 
   Serial.println(input_volt);// prints the voltage value in the serial monitor
   mySerial.println(input_volt );
   // lcd.setCursor(0, 1);
   // lcd.print("Voltage= ");               // prints the voltage value in the LCD display  
   // lcd.print(input_volt);
    delay(300);
   
}
 
