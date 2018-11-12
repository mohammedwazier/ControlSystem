void readWhiteSurface(){
  /* Sensor must be on white surface */
  for(int i=0;i<8;i++){
    mux(i);
    whiteSensor[i] = analogRead(sensor);
//    map(whiteSensor[i], 0, 1023, 0, 255);
//    whiteSensor[i] = whiteSensor[i]/4;
    sumWhite+=whiteSensor[i];
  }
  sumWhite = sumWhite/8;
  writeToMemory(1);
}

void readBlackSurface(){
  /* Sensor must be on black surface */
  for(int i=0;i<8;i++){
    mux(i);
    blackSensor[i] = analogRead(sensor);
//    map(blackSensor[i], 0, 1023, 0, 255);
//    blackSensor[i] = blackSensor[i]/4;
    sumBlack+=blackSensor[i];
  }
  sumBlack = sumBlack/8;
  writeToMemory(2);
}

void readSensor(){
  /* Just Read sensor */
  for(int i=0;i<8;i++){
    mux(i);
    analogBuffer[i]=analogRead(sensor);
//    map(analogBuffer[i], 0, 1023, 0, 255);
//    analogBuffer[i] = analogBuffer[i]/4;
  }
}
