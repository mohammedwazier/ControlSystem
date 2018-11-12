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
