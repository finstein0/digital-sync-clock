#include <SPI.h>
#include <DMD2.h>
#include <NMEAGPS.h>
#include <fonts/Arial14.h>
#include <fonts/Droid_Sans_12.h>

int H,M;
int a,b;//flags
int h,m,i;
char prevBuff[10];

// PICK ONE OF THESE PORT ALTERNATIVES
//
// BEST: connect GPS to pins 0 & 1, since you're not using Serial.
//             Requires disconnecting pin 0 to upload new sketch over USB.
#define gpsPort Serial1 // just an alias for Serial

// 2nd BEST: connect GPS to pins 8 & 9 (on an UNO)
//#include <AltSoftSerial.h>
//AltSoftSerial gpsPort

// 3rd BEST:
//#include <NeoSWSerial.h>
//NeoSWSerial gpsPort(3, 4); // RX, TX

// WORST: SoftwareSerial NOT RECOMMENDED
//#include <SoftwareSerial.h>
//SoftwareSerial myserial(15,14);

//SoftwareSerial gpsPort(15,14);

// Defining Constants
#define Length 1
#define Width 1

// Declaration Variable
SoftDMD dmd(Length, Width);                  // Length x Width

NMEAGPS gps; // parser

void setup()
{
  dmd.setBrightness(255);
  dmd.selectFont(Droid_Sans_12);
  dmd.begin();
  dmd.clearScreen();
  dmd.drawString(0,1,"gps.off");
delay(2000);
  gpsPort.begin(9600);
}

void loop()
{
  while (gps.available( gpsPort )) {
    gps_fix fix = gps.read();

    if (fix.valid.time) {
//       UTC_ind_zone_time
      char dmdBuff[10];
      H= (fix.dateTime.hours)+5;
      M= (fix.dateTime.minutes)+30;
      if (M>=60){ 
          M=M-60;   //set minutes
          H=H+1;    //increment hours
        }
        if (H>=24)   H=H-24;
        
        
      

      
      sprintf_P( dmdBuff, PSTR("%02d:%02d"),
                 H, M );


      
       Serial.print("previous: ");
      for (i=0; i<5; i++){  
      Serial.print(prevBuff[i]);
      
      }
      Serial.print("\n");
      for (i=0; i<5; i++){
        if (prevBuff[i]!=dmdBuff[i]) dmd.clearScreen();
        }
      
      
      
      dmd.drawString(3,3,dmdBuff);
      

      Serial.print("current: ");
      for (i=0; i<5; i++){  
      Serial.print(dmdBuff[i]);
      prevBuff[i]=dmdBuff[i];
      }
      
      Serial.print("\n");
    }
  }
}
