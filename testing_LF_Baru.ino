/*
  Coding V4
  Using New LF Module
  Created By Muhammad Waziruddin Akbar on 06/10/18.
  Copyright © 2018 Muhammad Waziruddin Akbar. All rights reserved.
*/

#include <Adafruit_SSD1306.h>
#include <Adafruit_GFX.h>
#include <EEPROM.h>

Adafruit_SSD1306 display(4);

int sensor = A0, s0 = A3, s1 = 11, s2 = 12;

int btn = 3, btn2 = 7;

const int MotorKa = 10;
const int in1 = A2; 
const int in2 = 8;

const int MotorKi = 9;
const int in3 = 6;
const int in4 = A1;

int SumError = 0;
double Kp = 14;
const int Ki = 0;
double Kd = 7;
const int Sp = 0;
const double Ts = 1;        // Time sampling

unsigned long MAXPWM = 200;
const int MINPWM = 0;
//const float intervalPWM = (MAXPWM - MINPWM) / 8;
int lastError=0;
int sError=0;

unsigned long Lpwm,Rpwm;

String binaryValue="00000000";
int sensorAvg[] = {255, 255, 255, 255, 255, 255, 255, 255};
int digitalBuffer[] = {0, 0, 0, 0, 0, 0, 0, 0};
int analogBuffer[] = {0, 0, 0, 0, 0, 0, 0, 0};
int whiteSensor[] = {0, 0, 0, 0, 0, 0, 0, 0};
int blackSensor[] = {0, 0, 0, 0, 0, 0, 0, 0};
int sumWhite = 0;
int sumBlack = 0;
double midSensor = 0;

int state = 0;
int calibrateStatus = 0;

int error = 0; //, SumError = 0, LastError = 0, offset = 0;

//int outPID;
unsigned long buttonMax = 0;

//int address = 0;

void setup() {
  pinMode(btn, INPUT);pinMode(btn2, INPUT);
  pinMode(s0, OUTPUT);pinMode(s1, OUTPUT);pinMode(s2, OUTPUT);
  
  pinMode(MotorKa, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  
  pinMode(MotorKi, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  
  pinMode(sensor, INPUT);
  
  Serial.begin(9600);
  
//  clearMemory();

  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);  // initialize with the I2C addr 0x3C (for the 128x32)

  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  
  display.setCursor(27,12);

  outerBox();
  if(EEPROM.read(0) > 0){
    //Do Read Sensor (Black & White), Read KD, Read KP and State from EEPROM
    readEeprom(0);
    readEeprom(1);
    readEeprom(2);
    readEeprom(3);
    readEeprom(4);
    Serial.print("EEPROM Telah di Set");
    display.println("EEPROM LOADED");  
    
  }else{
    display.println("Hello, world!");  
  }
  
  
  display.display();
  delay(5000);
//  delay(1000);
  display.clearDisplay();
  display.display();
}

void loop() {
  display.clearDisplay();
  buttonMax=millis()+1000;
  readSensor();
  convertBinary();
  setError();
    
    if(state == 0){
        while(!digitalRead(btn)){
          if(millis() >= buttonMax){ 
            state = 3; 
          }else{ 
            state = 1;
          }
        }
    }else if(state == 1){
        while(!digitalRead(btn)){
          if(millis() >= buttonMax){
          }else{
            state = 2;
          }
        }
    }else if(state == 2){
        while(!digitalRead(btn)){
          if(millis() >= buttonMax) state = 0; //break;
        }
    }else if(state == 3){
      if(!digitalRead(btn)){
        Kp=Kp+1;
        writeToMemory(3);
        while(!digitalRead(btn)){
          if(millis() >= buttonMax){ 
            state = 0;
          }
        }
      }
    }else if(state == 4){
      if(!digitalRead(btn)){
        Kd=Kd+1;
        writeToMemory(3);
        while(!digitalRead(btn)){
//          if(millis() >= buttonMax){
            //state = 0; break;
//          }
        }
      }
    }else if(state == 5){
      if(!digitalRead(btn)){
        MAXPWM = MAXPWM+1;
        while(!digitalRead(btn)){
//          if(millis() >= buttonMax){
//            
//          }
        }
      }
    }
  

  /*BTN 2 */
    if(state == 0){
        while(!digitalRead(btn2)){
          state = 5;
          if(millis() >= buttonMax) state=4;
        }      
    }else if(state == 3){
      if(!digitalRead(btn2)) {
        Kp=Kp-1;
        writeToMemory(3);
        while(!digitalRead(btn2)){
          
        }
      }
    }else if(state == 4){
      if(!digitalRead(btn2)){
        Kd=Kd-1;
        writeToMemory(4);
        while(!digitalRead(btn2)){
          if(millis() >= buttonMax){
            state=0;
          }
        }
      }
    }else if(state == 5){
      if(!digitalRead(btn2)){
        MAXPWM=MAXPWM-1;
        while(!digitalRead(btn2)){
          if(millis() >= buttonMax){
            state = 0;
          }
        }
      }
    }
    

  if(state == 0){
    if(calibrateStatus == 0){
      display.setCursor(16,7);
//      Serial.println("Need Calibration");
      display.print("Need Calibration");
    }else{
      /* Displaying binary Value from sensor */
      display.setCursor(38,7);
      display.print(error);
      pidSensor();
      boxSensor();
    }
    
   }else if(state == 1){
    rodaMati();
    readWhiteSurface();
    display.setCursor(2,2);
//    Serial.println("Put line Follower on the White Surface");
    display.print("Put Line Follower on the White Surface");
    display.setCursor(30, 15);
    display.print(sumWhite);
    calibrateStatus=2; 
   }else if(state == 2){
    rodaMati();
    readBlackSurface();
    display.setCursor(2,2);
//    Serial.println("Put line Follower on the Black Surface");
    display.print("Put Line Follower on the Black Surface");
    display.setCursor(30, 15);
    display.print(sumBlack);
    calibrateStatus=2;
    writeToMemory(0);
   }else if(state == 3){
    rodaMati();
    display.setCursor(30, 4);
    display.print("KP Menu");
    display.setCursor(30, 12);
    display.print(Kp);
   }else if(state == 4){
    rodaMati();
    display.setCursor(30, 4);
    display.print("KD Menu");
    display.setCursor(30, 12);
    display.print(Kd);
   }
  
  display.setCursor(64,120);
  display.print(state);
  
  outerBox();
  display.display();
}





