 
#include <TinyGPS++.h>
#include <SoftwareSerial.h>

// setup gps serial
int gpsTxPin = 8;
int gpsRxPin = 9;
//SoftwareSerial gpsSerial(gpsTxPin, gpsRxPin);
TinyGPSPlus gps;
void setup()
{
  Serial.begin(9600);  //set monitor to 9600

//  gpsSerial.begin(9600); //adjust for GPS unit

  Serial.println("Ready!");
}

void loop()
{
  while(Serial.available())
  { gps.encode(Serial.read());
    if (gps.location.isUpdated()){
      Serial.print("Latitude= "); 
      Serial.print(gps.location.lat(), 6);
      Serial.print(" Longitude= "); 
      Serial.println(gps.location.lng(), 6);
    }
  }
}
