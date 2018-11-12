//Write to EEPROM
void writeToMemory(int state) {
  switch(state){
    case 0:{
      //Set State Kalibrasi
      write_EEPROM(2, 0);
    };break;
    case 1:{
      //Set White Sensor
      int a=1;
      for(int i=0;i<8;i++){
        whiteSensor[i] = whiteSensor[i]/4;
//        map(whiteSensor[i], 0, 1023, 0, 255);
        write_EEPROM((whiteSensor[i]), a);
        a++;
      }
    };break;
    case 2:{
      //Set Black Sensor
      int a=11;
      for(int i=0;i<8;i++){
        blackSensor[i] = blackSensor[i]/4;
//        map(blackSensor[i], 0, 1023, 0, 255);
        write_EEPROM((blackSensor[i]), a);
        a++;
      }
    };break;
    case 3:{
      //KP
      write_EEPROM(Kp, 21);
    };break;
    case 4:{
      //KD
      write_EEPROM(Kd, 22);
    };break;
  }
//  EEPROM.commit();
}

void write_EEPROM(int b, const int pos) {
    EEPROM.write(pos, b);
}

//Clear EEPROM
void clearMemory(){
  for (int i = 0 ; i < 1024 ; i++) {
    EEPROM.write(i, 0);
  }
//  EEPROM.commit();
}

//Read EEPROM
void readEeprom(int state){
  switch(state){
    case 0:{
      //Read State Kalibrasi
      calibrateStatus = EEPROM.read(0);
    };break;
    case 1:{
      //Read Black Sensor
      int a=1;
      for(int i=0;i<8;i++){
        whiteSensor[i] = EEPROM.read(a);
        whiteSensor[i] = whiteSensor[i] * 4;
        Serial.println(whiteSensor[i]);
//        delay(500);
        a++;
      }
    };break;
    case 2:{
      //Read Black Sensor
      unsigned int a=11;
      for(int i=0;i<8;i++){
        blackSensor[i] = EEPROM.read(a);
        blackSensor[i] = blackSensor[i] * 4;
        Serial.println(blackSensor[i]);
//        delay(500);
        a++;
      }
    };break;
    case 3:{
      //Read KP
      Kp = EEPROM.read(21);
    };break;
    case 4:{
      //Read KD
      Kd = EEPROM.read(22);
    };break;
  }
}

//String read_string(int l, int p){
//  String temp;
//  for (int n = p; n < l+p; ++n)
//    {
//     if(char(EEPROM.read(n))!=';'){
//        if(isWhitespace(char(EEPROM.read(n)))){
//          //do nothing
//        }else temp += String(char(EEPROM.read(n)));
//      
//     }else n=l+p;
//     
//    }
//  return temp;
//}
