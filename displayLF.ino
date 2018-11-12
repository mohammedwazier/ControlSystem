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

void boxSensor(){
  int outBoxTop = 16;
  int outBox = 6;
  int inBoxTop = 18;
  int inBox = 2;
  
  //Outer Rect
    display.drawRect(32,outBoxTop,outBox,outBox, WHITE);
    display.drawRect(40,outBoxTop,outBox,outBox, WHITE);
    display.drawRect(48,outBoxTop,outBox,outBox, WHITE);
    display.drawRect(56,outBoxTop,outBox,outBox, WHITE);
    display.drawRect(64,outBoxTop,outBox,outBox, WHITE);
    display.drawRect(72,outBoxTop,outBox,outBox, WHITE);
    display.drawRect(80,outBoxTop,outBox,outBox, WHITE);
    display.drawRect(88,outBoxTop,outBox,outBox, WHITE);
    
    //Inner React
    if(digitalBuffer[0]==1){
      display.fillRect(34,inBoxTop,inBox,inBox,WHITE);  
    }
    if(digitalBuffer[1]==1){
      display.fillRect(42,inBoxTop,inBox,inBox,WHITE);
    }
    if(digitalBuffer[2]==1){
      display.fillRect(50,inBoxTop,inBox,inBox,WHITE);
    }
    if(digitalBuffer[3]==1){
      display.fillRect(58,inBoxTop,inBox,inBox,WHITE);
    }
    if(digitalBuffer[4]==1){
      display.fillRect(66,inBoxTop,inBox,inBox,WHITE);
    }
    if(digitalBuffer[5]==1){
      display.fillRect(74,inBoxTop,inBox,inBox,WHITE);
    }
    if(digitalBuffer[6]==1){
      display.fillRect(82,inBoxTop,inBox,inBox,WHITE);
    }
    if(digitalBuffer[7]==1){
      display.fillRect(90,inBoxTop,inBox,inBox,WHITE);
    }
}
