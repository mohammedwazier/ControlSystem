/*
  Latihan Assesment 1
  Coding V3
  Created By Muhammad Waziruddin Akbar on 30/09/18.
  Copyright © 2018 Muhammad Waziruddin Akbar. All rights reserved.
*/

//#include <EEPROM.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_GFX.h>
//
Adafruit_SSD1306 display(4);

/* define PIN INPUT OUTPUT */
#define sensor A0

const int s0=A3;
const int s1=11;
const int s2=12;


const int in1=10,in2=8,en1=A2;//EN = PWM
const int in3=9,in4=6,en2=A1;//EN = PWM
const int btn=3,btn2=7;

String binaryValue="00000000";

int error=0;
//int lastError=0;

int Kp = 1;
int Sp = 0;
int MAXPWM = 90;
int MINPWM = 0;
float intervalPWM = (MAXPWM - MINPWM) / 8;

int lPWM;
int rPWM;

int state=0;
int menu=0, buttonMax=0, calibrateStatus=0;

int sensorAvg[] = {512, 512, 512, 512, 512, 512, 512, 512};
int digitalBuffer[] = {0, 0, 0, 0, 0, 0, 0, 0};
int analogBuffer[] = {0, 0, 0, 0, 0, 0, 0, 0};
int whiteSensor[] = {0, 0, 0, 0, 0, 0, 0, 0};


void setup() {
  pinMode(in1, OUTPUT);pinMode(in2, OUTPUT);pinMode(en1, OUTPUT);
  pinMode(in3, OUTPUT);pinMode(in4, OUTPUT);pinMode(en2, OUTPUT);
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
//  outerBox();

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
  setError();
  
  //run
  
  
//  lastError=error;
  
  while(digitalRead(btn)==LOW){
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
      /* Displaying binary Value from sensor */
        display.setCursor(16,7);
        display.print(binaryValue);
//        Serial.println(binaryValue);
//      errorToPWM();
//      lineFollow();
//      driverMotor();
    }
    
    //Outer Rect
    display.drawRect(32,16,6,6, WHITE);
    display.drawRect(40,16,6,6, WHITE);
    display.drawRect(48,16,6,6, WHITE);
    display.drawRect(56,16,6,6, WHITE);
    display.drawRect(64,16,6,6, WHITE);
    display.drawRect(72,16,6,6, WHITE);
    display.drawRect(80,16,6,6, WHITE);
    display.drawRect(88,16,6,6, WHITE);

//    //Inner React
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
     readWhiteSurface();
     calibrateStatus=1;
   }
   display.display();
}

void readWhiteSurface(){
  /* Sensor must be on white surface */
  for(int i=0;i<8;i++){
//    mux(i);
    whiteSensor[i]=analogRead(sensor);
  }
}

void readSensor(){
  /* Just Read sensor */
  for(int i=0;i<8;i++){
    mux(i);
//    r0 = bitRead(i,0);
//
//    r1 = bitRead(i,1);
//
//    r2 = bitRead(i,2);
    
    if(calibrateStatus == 0){
      whiteSensor[i]=analogRead(sensor);
    }else{
      analogBuffer[i]=analogRead(sensor);
    }
  }
}
void convertBinary(){
  for(int i=0;i<8;i++){
    /* Increase value from base sensor value (Black Line) */
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
      binaryValue+="1";
      digitalBuffer[i]=1;
    }else{
      binaryValue+="0";
      digitalBuffer[i]=0;
    }
  }
}

void setError(){
  if(binaryValue=="10000000"){
    error=6;
  }else if(binaryValue=="11000000" || binaryValue=="1110000"){
    error=5;
  }else if(binaryValue=="01000000"){
    error=4;
  }else if(binaryValue=="01100000"){
    error=3;
  }else if(binaryValue=="00100000"){
    error=2;
  }else if(binaryValue=="00110000" || binaryValue=="01110000"){
    error=1;
  }else if(binaryValue=="00010000" || binaryValue=="00011000" || binaryValue=="00001000" || binaryValue=="00111000" || binaryValue=="00011100"){
    error=0;
  }else if(binaryValue=="00001100" || binaryValue=="00001110"){
    error=-1;
  }else if(binaryValue=="00000100"){
    error=-2;
  }else if(binaryValue=="00000110"){
    error=-3;
  }else if(binaryValue=="00000010"){
    error=-4;
  }else if(binaryValue=="00000011" || binaryValue=="00000111"){
    error=-5;
  }else if(binaryValue=="00000001"){
    error=-6;
  }else{
    if(error<0){
      error=-7;
    }else{
      error=7;
    }
  }
}
//void lineFollow() {
////  robotPosition();
//  int SetPoint = 0;                       // Setpoint yang diinginkan
//  Error = SetPoint - error;                 // Error
//  double DeltaError = Error - LastError;  // Delta Error (Selisih error sekarang e(t) dengan error sebelumya e(t-1))
//  SumError += LastError;                  // Akumulasi error
//  double P = Kp * Error;                  // Kontrol proporsional
//  double I = Ki * SumError * Ts;          // Kontrol integral
//  double D = ((Kd / Ts) * DeltaError);    // Kontrol derivative
//  LastError = Error;                      // Error sebelumnya
//  outPID = P + I + D;                     // Output PID
//
//  motorKi = BasePWM - outPID + offset;
//  motorKa = BasePWM + outPID + offset;
//  /*** Pembatasan kecepatan ***/
//  if (motorKi > BasePWM)motorKi = BasePWM;
//  if (motorKi < 0)motorKi = 0;
//  if (motorKa > BasePWM)motorKa = BasePWM;
//  if (motorKa < 0)motorKa = 0;
//}
//void driverMotor(){
//  if(Pos>4){
//     digitalWrite(in1, LOW);
//     analogWrite(en1, BasePWM - motorKa);
//  }else{
//    digitalWrite(in1, HIGH);
//    analogWrite(en1, motorKa);
//  }
//  if(Pos<-4){
//    digitalWrite(in2, LOW);
//    analogWrite(en2, BasePWM - motorKi);
//  }else{
//    digitalWrite(in2, HIGH);
//    analogWrite(en2, motorKi);
//  }
//}

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
