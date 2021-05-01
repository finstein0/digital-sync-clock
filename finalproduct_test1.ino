#include <SoftwareSerial.h>
#include <SPI.h>
#include <DMD2.h>
#include <fonts/Arial14.h>
#include <fonts/Droid_Sans_16.h>
#include <fonts/Droid_Sans_12.h>
#include <fonts/SystemFont5x7.h>

int a =0;
int b =0;
const int BUFFER_SIZE = 100;
char buf[BUFFER_SIZE];
char prevbuf[BUFFER_SIZE]="00:00:00";

SoftDMD dmd(1,1);  // DMD controls the entire display
DMD_TextBox box(dmd, 1, 0, 32, 16);  // "box" provides a text box to automatically write to/scroll the display



int length=8;



void setup() {
  Serial.begin(9600); // opens serial port, sets data rate to 9600 bps
  dmd.setBrightness(255);
  dmd.selectFont(Droid_Sans_12);
  dmd.begin();
}

void loop() {
  // check if data is available
  if (Serial.available() > 0) {
    // read the incoming bytes:
    int rlen = Serial.readBytesUntil('U', buf, BUFFER_SIZE);

    dmd.drawChar(1,2,buf[3]);
    dmd.drawChar(9,2,buf[4]);
    dmd.drawChar(15,1,':');
    dmd.drawChar(17,2,buf[6]);
    dmd.drawChar(25,2,buf[7]);
    b=1;

    
    // prints the received data
    for(int i = 0; i < rlen; i++){
      prevbuf[i]=buf[i];
    }
  }



  
  //else{
      //00:00:09
      


      
      for(int i = 0; i < length; i++){
      Serial.print(prevbuf[i]);
      //lcd.print(prevbuf[i]);
      if(i==2 || i==5){
        continue;
      }
      if(i==7){
        prevbuf[i]=prevbuf[i]+1;//s1
        if (prevbuf[i]=='1'){a=a+1;}
        if (prevbuf[i]=='5'){a=a+1;}
        if(prevbuf[i]>=':'){
          prevbuf[i]='0';
          prevbuf[i-1]=prevbuf[i-1]+1;//s2
          if (prevbuf[i-1]=='1'){a=a+1;}
          if (prevbuf[i-1]=='5'){a=a+1;}
          if (prevbuf[i-1]>='6'){ 
            prevbuf[i-1]='0'; 
            prevbuf[i-3]=prevbuf[i-3]+1;//m1
            if (prevbuf[i-3]=='1'){a=a+1;} ///flag increment
            if (prevbuf[i-3]=='5'){a=a+1;}
            if (prevbuf[i-3]==':'){
              prevbuf[i-3]='0';
              prevbuf[i-4]=prevbuf[i-4]+1;//m2
              if (prevbuf[i-4]=='5'){a=a+1;}
              if (prevbuf[i-4]=='1'){a=a+1;} ///flag increment
              if (prevbuf[i-4]=='6'){
                prevbuf[i-4]='0'; 
                prevbuf[i-6]=prevbuf[i-6]+1;//h1
                if (prevbuf[i-6]=='5'){a=a+1;}
                if (prevbuf[i-6]=='1'){a=a+1;} ///flag increment
                if (prevbuf[i-6]==':'){
                  prevbuf[i-6]='0';
                  prevbuf[i-7]=prevbuf[i-7]+1; //h2
                  if (prevbuf[i-7]=='5'){a=a+1;}
                  if (prevbuf[i-7]=='1'){a=a+1;} ///flag increment                 
                  }   
                }
              }    
            }
        }
      
      }
      if ((prevbuf[i-7]==2)&&(prevbuf[i-6]==5)){
                  prevbuf[i-7]=0;
                  prevbuf[i-7]=0;
                  }
    }//forend
    
    /*
     * 0,1=hours
     * 3,4=min
     * 6,7=sec
     * 
     * 
     */

    // if (b>1) { continue; }

     if (b==0) {
      
      
     if (a>0) {
        dmd.clearScreen();
        a=0;
      }
      
    dmd.drawChar(1,2,prevbuf[3]);
    dmd.drawChar(9,2,prevbuf[4]);
    dmd.drawChar(15,1,':');
    dmd.drawChar(17,2,prevbuf[6]);
    dmd.drawChar(25,2,prevbuf[7]);
     }
     
    Serial.print("\n");
//}//else end



  b = 0;
  delay(1000);
  
}
