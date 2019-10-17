
  
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
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
RF24 radio(7, 8);
// nRF24L01 (CE, CSN)
 SoftwareSerial mySerial(9, 10);
const byte address[6] = "00001";
unsigned long lastReceiveTime = 0;
unsigned long currentTime = 0;

struct Data_Package {
  float voltage;
};
Data_Package data;
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
 

void setup()
{
  mySerial.begin(9600);   // Setting the baud rate of GSM Module  
  Serial.begin(9600);    // Setting the baud rate of Serial Monitor (Arduino)
  delay(100);
  radio.begin();
  radio.openReadingPipe(0, address);
  radio.setAutoAck(false);
  radio.setDataRate(RF24_250KBPS);
  radio.setPALevel(RF24_PA_LOW);
  radio.startListening(); //  Set the module as receiver
  resetData();
}
 

void loop()
{
 // Check whether there is data to be received
  if (radio.available()) {
    radio.read(&data, sizeof(Data_Package)); // Read the whole data and store it into the 'data' structure
    lastReceiveTime = millis(); // At this moment we have received the data
  }
  // Check whether we keep receving data, or we have a connection between the two modules
  currentTime = millis();
  if ( currentTime - lastReceiveTime > 1000 ) { // If current time is more then 1 second since we have recived the last data, that means we have lost connection
    resetData(); // If connection is lost, reset the data. It prevents unwanted behavior, for example if a drone has a throttle up and we lose connection, it can keep flying unless we reset the values
  }
  // Print the data in the Serial Monitor
  Serial.print("Voltage");
  Serial.println(data.voltage);
  delay(500);
  
  //if (Serial.available()>0)
  // switch(Serial.read())
 // {
  //  case 's': 
   if(data.voltage>2.0)
      SendMessage();
     // break;
  

 if (mySerial.available()>0)
   Serial.write(mySerial.read());
}
void SQLUpload(){
  GPS.begin(9600);
  Serial.begin(9600);
  getGPS();
  Serial.println(LAT/1000000,8);
  Serial.println(LON/1000000,8);
  mySerial.println("AT+CGATT?");
  delay(100);
  mySerial.println("AT+SAPBR=3,1,\"Contype\",\"GPRS\"");
  delay(2000);
  mySerial.println("AT+SAPBR=3,1,\"APN\",\"idea\"");
  delay(2000);
  mySerial.println("AT+SAPBR=1,1");
  delay(2000);
  mySerial.println("AT+SAPBR=2,1");
  delay(500);
  mySerial.println("AT+HTTPINIT");
  delay(2000);
  mySerial.println("AT+HTTPPARA=\"CID\",1");
  delay(500);
  // HTTP URL Posting    
      String url;
      url +=F("AT+HTTPPARA=\"URL\",\"http://www.innovaim.in/write.php?lat=");
      url +=String(LAT/1000000,8);
      url += F("&lon=");
      url +=String(LON/1000000,8);
      url += F("&lin=");
      url += F("http://maps.google.com/maps?saddr=My%20location%26daddr=");
      url += String(LAT/1000000,8);
      url += F(",");
      url += String(LON/1000000,8);
      url +=F("%26mode=driving\"");
      mySerial.println(url);
      Serial.println(url);


   //   mySerial.println("AT+HTTPPARA=\"URL\",\"http://www.innovaim.in/write.php?lat=77&lon=11&lin=abelipload\"");
      delay(8000);
      mySerial.println("AT+HTTPACTION=0");
      delay(7000);
      mySerial.println("AT+HTTPREAD");
      delay(2000);
      mySerial.println("AT+HTTPTERM");
      delay(1000);
      mySerial.println("AT+SAPBR=0,1");
      delay(500);
      Serial.println("Server Upload Successful");
}

 void SendMessage()
{
  SQLUpload();
  mySerial.println("AT+CMGF=1");    //Sets the GSM Module in Text Mode
  delay(1000);  // Delay of 1000 milli seconds or 1 second
  mySerial.println("AT+CMGS=\"+919074056134\"\r"); // Replace x with mobile number
  delay(1000);
  GPS.begin(9600);
  Serial.begin(9600);
  getGPS();
 //https://www.google.com/maps/dir/'10.462682,76.040111'/'11.32074546,75.93459320'/ 
  String buf;
     buf += F("http://maps.google.com/maps?saddr=My%20location&daddr=");
     buf += String(LAT/1000000,8);
     buf += F(",");
     buf += String(LON/1000000,8);
     buf +=F("&mode=driving");
     mySerial.print("Lat:");
     mySerial.println(LAT/1000000,8);
     Serial.println(LAT/1000000,8);
     mySerial.print("Lon:");
     mySerial.println(LON/1000000 ,8);
     Serial.println(LON/1000000,8);
     mySerial.print("Link:");
     mySerial.println(buf);
  // The SMS text you want to send
     delay(100);
     mySerial.println((char)26);// ASCII code of CTRL+Z
     delay(1000);
    
}

void resetData() {
  // Reset the values when there is no radio connection - Set initial default values
  float voltage = 0.0;
}
