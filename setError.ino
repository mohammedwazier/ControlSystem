void convertBinary(){
  sError=0;
  binaryValue="";
  for(int i=0;i<8;i++){
    /* Increase value from base sensor value (Black Line) */

    sensorAvg[i] = ((blackSensor[i]-whiteSensor[i])/2)+(whiteSensor[i]*0.90);
    
    if(analogBuffer[i] > sensorAvg[i]){
      binaryValue+="1";
      digitalBuffer[i] = 1;
      sError++;
    }else{
      binaryValue+="0";
      digitalBuffer[i] = 0;
    }
  }
}

void setError(){
  if(sError==4 || sError==3){
    error = ((digitalBuffer[0]*4)+(digitalBuffer[1]*3)+(digitalBuffer[2]*2)+(digitalBuffer[3]*1))-((digitalBuffer[4]*1)+(digitalBuffer[5]*2)+(digitalBuffer[6]*3)+(digitalBuffer[7]*4));  
  }
  
  if(error == 9){
    error = 9;
  }else if(error == -9){
    error = -9;
  }
  if(error == 9 && digitalBuffer[0] == 1 && digitalBuffer[1] == 1){
    error = 10;
  }else if(error >= 9 && digitalBuffer[0] == 1){
    error = 11;
  }
  
  if(error == -9 && digitalBuffer[7] == 1 && digitalBuffer[6] == 1){
    error = -10;
  }else if(error <= -9 && digitalBuffer[7] == 1){
    error = -11;
  }
  if(error >= 11){
    error = 12;
  }else if(error <= -11){
    error = -12;
  }
  
//  if(binaryValue == "00000000"){
//    if(lastError < 0){
//      error = -11;
//    }else{
//      error = 11;
//    }
//  }
//  if(binaryValue=="00011000" || binaryValue=="00011100" || binaryValue=="00111000" || binaryValue=="00111100"){
//    error=0;
//  }else if(binaryValue=="00110000" || binaryValue=="01110000" || binaryValue=="01111000"){
//    error=1;
//  }else if(binaryValue=="01100000" || binaryValue=="11100000" || binaryValue=="11110000"){
//    error=2;
//  }else if(binaryValue=="11000000" || binaryValue=="10000000"){
//    error=3;
//  }else if(binaryValue=="00001100" || binaryValue=="00001110" || binaryValue=="00011110"){
//    error=-1;
//  }else if(binaryValue=="00000110" || binaryValue=="00000111" || binaryValue=="00001111"){
//    error=-2;
//  }else if(binaryValue=="00000011" || binaryValue=="00000001"){
//    error=-3;
//  }else{
//    if(error<0){
//      error =-4;
//    }else{
//      error=4;
//    }
//  }
}
