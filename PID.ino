void pidSensor(){
  int setRoda = 0;
  int setPoint = 0;
  int err = setPoint - error;
  double DeltaError = error - lastError;    // Delta Error (Selisih error sekarang e(t) dengan error sebelumya e(t-1))
  SumError += lastError;                    // Akumulasi error
  int rate = error - lastError;             //
  int P = Kp * err;                         // Kontrol Proportional
  double I = Ki * SumError * Ts;            // Kontrol Integral
//  double D = ((Kd / Ts) * DeltaError);    // Kontrol Derivative
  double D = (Kp * error) + (rate * Kd);    // Kontrol Derivative 2
  lastError=error;
  
//  int MV = P + D;
   int MV = D;
//  long MV = P + I + D;
  
  Lpwm = MAXPWM - MV;
  Rpwm = MAXPWM + MV;
  Rpwm = (Rpwm*0.10) + Rpwm;

  if (Lpwm > MAXPWM) Lpwm = MAXPWM;
  if (Lpwm < 0) Lpwm = 0;
  if (Rpwm > MAXPWM) Rpwm = MAXPWM;
  if (Rpwm < 0) Rpwm = 0;
  
//  if(error == -9){
//    //Kanan mati
//    digitalWrite(in1, LOW);
//    digitalWrite(in2, HIGH);
//    analogWrite(MotorKa, Rpwm);
//     
//    digitalWrite(in3, HIGH);
//    digitalWrite(in4, LOW);
//    analogWrite(MotorKi, Lpwm); 
//    setRoda = 1;
//  }
  
//  if(error == 4){
//    //Kiri mati
//    digitalWrite(in3, LOW);
//    digitalWrite(in4, HIGH);
//    analogWrite(MotorKi, Lpwm);
//      
//    digitalWrite(in1, HIGH);
//    digitalWrite(in2, LOW);
//    analogWrite(MotorKa, Rpwm);
//    setRoda = 1;
//  }

//  if(setRoda == 0){
    if(error == -12){
      digitalWrite(in1, HIGH);
      digitalWrite(in2, LOW);
      analogWrite(MotorKa, MAXPWM);
      
      digitalWrite(in3, LOW);
      digitalWrite(in4, LOW);
      analogWrite(MotorKi, Lpwm); 
    }else if(error == 12){
      digitalWrite(in1, LOW);
      digitalWrite(in2, LOW);
      analogWrite(MotorKa, Rpwm);
      
      digitalWrite(in3, HIGH);
      digitalWrite(in4, LOW);
      analogWrite(MotorKi, MAXPWM); 
    }else{
      digitalWrite(in1, HIGH);
      digitalWrite(in2, LOW);
      analogWrite(MotorKa, Rpwm);
      
      digitalWrite(in3, HIGH);
      digitalWrite(in4, LOW);
      analogWrite(MotorKi, Lpwm);   
    }
//    digitalWrite(in1, HIGH);
//    digitalWrite(in2, LOW);
//    analogWrite(MotorKa, Rpwm);
//    
//    digitalWrite(in3, HIGH);
//    digitalWrite(in4, LOW);
//    analogWrite(MotorKi, Lpwm); 
//  }
}

void rodaMati(){
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  analogWrite(MotorKa, 0);
  
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
  analogWrite(MotorKi, 0);
}

