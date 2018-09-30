/*
  Latihan Assesment 1
  Coding V3
  Created By Muhammad Waziruddin Akbar on 30/09/18.
  Copyright © 2018 Muhammad Waziruddin Akbar. All rights reserved.
*/

#include <EEPROM.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_GFX.h>

Adafruit_SSD1306 display(4);

/* define PIN INPUT OUTPUT */
const int sensor = A0;

const int s0=12;
const int s1=8;
const int s2=7;

const int in1=3,en1=5;//EN = PWM
const int in2=9,en2=6;//EN = PWM
const int btn=2,btn2=4;

String binaryValue="00000000";

//int RPWM = 255;
//int LPWM = 255;

unsigned int state=0;
unsigned int stateMenu=2, menu=0, buttonMax=0, calibrateStatus=0;

//state
//boolean buttonState=false;

//define Array Value Sensor
//float sensorValueMin[] = {1023, 1023, 1023, 1023, 1023, 1023, 1023, 1023};
//float sensorValueMax[] = {0, 0, 0, 0, 0, 0, 0, 0, 0};
//int threshold[] = {10, 10, 10, 10, 10, 10, 10, 10};

int sensorAvg[] = {512, 512, 512, 512, 512, 512, 512, 512};
int digitalBuffer[] = {0, 0, 0, 0, 0, 0, 0, 0};
int analogBuffer[] = {0, 0, 0, 0, 0, 0, 0, 0};
int whiteSensor[] = {0, 0, 0, 0, 0, 0, 0, 0};


void setup() {
  pinMode(in1, OUTPUT);pinMode(en1, OUTPUT);
  pinMode(in2, OUTPUT);pinMode(en2, OUTPUT);
  pinMode(btn, INPUT);pinMode(btn2, INPUT);
  pinMode(s0, OUTPUT);pinMode(s1, OUTPUT);pinMode(s2, OUTPUT);
  pinMode(sensor, INPUT);
  Serial.begin(9600);
  
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);  // initialize with the I2C addr 0x3C (for the 128x32)

  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);

  display.setCursor(27,12);
  display.println("Hello, world!");
  outerBox();

  display.display();
  delay(2000);
  display.clearDisplay();
  display.display();
}

void loop() {
  display.clearDisplay();
  buttonMax=millis()+2000;
  binaryValue="";
  readSensor();
  convertBinary();
  
  
  while(digitalRead(btn)==HIGH){
    if(state == 0){
      if(millis() >= buttonMax){   
       state=2;
       break;
      }
    }else if(state == 2){
      if(millis() >= buttonMax){
        state=0;
        break;
      }
    }
  }
  
  if(state == 0){
    if(calibrateStatus == 0){
      display.setCursor(16,7);
      display.print("Need Calibration");
    }else{
      
    }
    display.setCursor(2,2);
    display.print(binaryValue);
    //Outer Rect
    display.drawRect(32,16,6,6, WHITE);
    display.drawRect(40,16,6,6, WHITE);
    display.drawRect(48,16,6,6, WHITE);
    display.drawRect(56,16,6,6, WHITE);
    display.drawRect(64,16,6,6, WHITE);
    display.drawRect(72,16,6,6, WHITE);
    display.drawRect(80,16,6,6, WHITE);
    display.drawRect(88,16,6,6, WHITE);

    //Inner React
    if(digitalBuffer[0]==1){
      display.fillRect(34,18,2,2,WHITE);  
    }
    if(digitalBuffer[1]==1){
      display.fillRect(42,18,2,2,WHITE);
    }
    if(digitalBuffer[2]==1){
      display.fillRect(50,18,2,2,WHITE);
    }
    if(digitalBuffer[3]==1){
      display.fillRect(58,18,2,2,WHITE);
    }
    if(digitalBuffer[4]==1){
      display.fillRect(66,18,2,2,WHITE);
    }
    if(digitalBuffer[5]==1){
      display.fillRect(74,18,2,2,WHITE);
    }
    if(digitalBuffer[6]==1){
      display.fillRect(82,18,2,2,WHITE);
    }
    if(digitalBuffer[7]==1){
      display.fillRect(90,18,2,2,WHITE);
    }
   }else if(state == 2){
    display.setCursor(2,2);
    display.print("Put Line Follower on the white Surface");
//   }else if(state == 1){
     readWhiteSurface();
     calibrateStatus=1;
    
   }
   outerBox();
  
   display.display();
}
void outerBox(){
  /* Display outer White line */
  for(int i=0;i<128;i++){
    display.drawPixel(i, 0, WHITE);
    display.drawPixel(i, 31, WHITE);
  }
  for(int i=0;i<32;i++){
    display.drawPixel(0, i, WHITE);
    display.drawPixel(127, i, WHITE);
  }
}

void readWhiteSurface(){
  /* Sensor must be on white surface */
  for(int i=0;i<8;i++){
    mux(i);
    whiteSensor[i]=analogRead(sensor);
  }
}

void readSensor(){
  /* Just Read sensor */
  for(int i=0;i<8;i++){
    mux(i);
    analogBuffer[i]=analogRead(sensor);
  }
}
void convertBinary(){
  for(int i=0;i<8;i++){
    /* Increase value from base value */
    if(whiteSensor[i] < 10){
      sensorAvg[i] = whiteSensor[i] + 60 + (whiteSensor[i] * 5);
    }else if(whiteSensor[i] < 30){
      sensorAvg[i] = whiteSensor[i] + 50 + (whiteSensor[i] * 3);
    }else if(whiteSensor[i] < 100){
      sensorAvg[i] = whiteSensor[i] + (whiteSensor[i] * 3);
    }else if(whiteSensor[i] < 200){
      sensorAvg[i] = whiteSensor[i] + ((whiteSensor[i] * 2));
    }
    
    if(analogBuffer[i] > sensorAvg[i]){
      binaryValue+="0";
      digitalBuffer[i]=0;
    }else{
      binaryValue+="1";
      digitalBuffer[i]=1;
    }
    Serial.print(i);
    Serial.print(" : ");
    Serial.print(whiteSensor[i]);
    Serial.print(" | ");
    Serial.print(analogBuffer[i]);
    Serial.print(" | ");
    Serial.print(sensorAvg[i]);
    Serial.println();
//    delay(200);
  }
  Serial.println();
}

void runningMotor(int a, int b){
  /* Range 0-100 to run the Motor */
  double mapA = map(a, 0,100, 0,255);
  double mapB = map(b, 0,100, 0,255);
  digitalWrite(in1, HIGH);
  digitalWrite(in2, HIGH);
  analogWrite(en1, mapA);
  analogWrite(en2, mapB);
}

void mux(int y){
  if (y==0){
    digitalWrite(s0,LOW);
    digitalWrite(s1,LOW);
    digitalWrite(s2,LOW);
  }
  else if (y==1){
    digitalWrite(s0,HIGH);
    digitalWrite(s1,LOW);
    digitalWrite(s2,LOW);
  }
  else if (y==2){
    digitalWrite(s0,LOW);
    digitalWrite(s1,HIGH);
    digitalWrite(s2,LOW);
  }
  else if (y==3){
    digitalWrite(s0,HIGH);
    digitalWrite(s1,HIGH);
    digitalWrite(s2,LOW);
  }
  else if (y==4){
    digitalWrite(s0,LOW);
    digitalWrite(s1,LOW);
    digitalWrite(s2,HIGH);
  }
  else if (y==5){
    digitalWrite(s0,HIGH);
    digitalWrite(s1,LOW);
    digitalWrite(s2,HIGH);
  }
  else if (y==6){
    digitalWrite(s0,LOW);
    digitalWrite(s1,HIGH);
    digitalWrite(s2,HIGH);
  }
  else if (y==7){
    digitalWrite(s0,HIGH);
    digitalWrite(s1,HIGH);
    digitalWrite(s2,HIGH);
  }
  else {
    digitalWrite(s0,LOW);
    digitalWrite(s1,LOW);
    digitalWrite(s2,LOW);
  }
}
