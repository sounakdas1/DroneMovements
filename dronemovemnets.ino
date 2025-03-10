int motorA_in1 = 4;////// direction same with C
int motorA_in2 = 5;
int motorA_pwm = 6;

int motorB_in1 = 7;
int motorB_in2 = 8; ////// direction same with D
int motorB_pwm = 9;

int motorC_in1 = 11;
int motorC_in2 = 12;
int motorC_pwm = 10;

int motorD_in1 = 2;
int motorD_in2 = 13;
int motorD_pwm = 3;

int standbyPin = 10; 
char cmd;
int speed = 255;

void setup() {
  Serial.begin(11200);
  pinMode(motorA_in1, OUTPUT);
  pinMode(motorA_in2, OUTPUT);
  pinMode(motorA_pwm, OUTPUT);

  pinMode(motorB_in1, OUTPUT);
  pinMode(motorB_in2, OUTPUT);
  pinMode(motorB_pwm, OUTPUT);

  pinMode(motorC_in1, OUTPUT);
  pinMode(motorC_in2, OUTPUT);
  pinMode(motorC_pwm, OUTPUT);

  pinMode(motorD_in1, OUTPUT);
  pinMode(motorD_in2, OUTPUT);
  pinMode(motorD_pwm, OUTPUT);

  pinMode(standbyPin, OUTPUT);  

  digitalWrite(standbyPin, HIGH);
}

void loop() {
  if (Serial.available()){
    cmd = Serial.read();
    if(cmd == 'T'){
      throttleUp(speed);
    }
    else if(cmd == 't'){
      throttledown(speed);
    }
    
    else if(cmd == 'P'){
      pitchforward(speed);
    }
    else if(cmd == 'p'){
      pitchbackward(speed);
      
    }
    else if(cmd == 'R'){
      rotateright(speed);
      

    }else if(cmd == 'r'){
      rotateleft(speed);
       
    }
    else if(cmd == 'Y'){
      yawleft(speed);
      
    }
    else if(cmd == 'y'){
      yawright(speed);
 
    }
    else if(cmd == 'A'){
      speedup(speed);
    }
    else if(cmd == 'a'){
      speeddown(speed);
    }
  }
}
void throttleUp(int speed){
      digitalWrite(motorA_in1, HIGH);
      digitalWrite(motorA_in2, LOW);
      analogWrite(motorA_pwm, speed); 

      digitalWrite(motorB_in1, LOW);
      digitalWrite(motorB_in2, HIGH);
      analogWrite(motorB_pwm, speed);  

      digitalWrite(motorC_in1, HIGH);
      digitalWrite(motorC_in2, LOW);
      analogWrite(motorC_pwm, speed); 

      digitalWrite(motorD_in1, LOW);
      digitalWrite(motorD_in2, HIGH);
      analogWrite(motorD_pwm, speed);  
}
void throttledown(int speed){
      digitalWrite(motorA_in1, HIGH);
      digitalWrite(motorA_in2, LOW);
      analogWrite(motorA_pwm, speed/2);  

     
      digitalWrite(motorB_in1, LOW);
      digitalWrite(motorB_in2, HIGH);
      analogWrite(motorB_pwm, speed/2); 

      digitalWrite(motorC_in1, HIGH);
      digitalWrite(motorC_in2, LOW);
      analogWrite(motorC_pwm, speed/2); 

      digitalWrite(motorD_in1, LOW);
      digitalWrite(motorD_in2, HIGH);
      analogWrite(motorD_pwm, speed/2);   
}
void pitchforward(int speed){
      digitalWrite(motorA_in1, HIGH);
      digitalWrite(motorA_in2, LOW);
      analogWrite(motorA_pwm, speed); 
    
      digitalWrite(motorB_in1, LOW);
      digitalWrite(motorB_in2, HIGH);
      analogWrite(motorB_pwm, speed); 

      digitalWrite(motorC_in1, HIGH);
      digitalWrite(motorC_in2, LOW);
      analogWrite(motorC_pwm, speed/2); 

      digitalWrite(motorD_in1, LOW);
      digitalWrite(motorD_in2, HIGH);
      analogWrite(motorD_pwm, speed/2);   
}
void pitchbackward(int speed){
      digitalWrite(motorA_in1, HIGH);
      digitalWrite(motorA_in2, LOW);
      analogWrite(motorA_pwm, speed/2);  

  
      digitalWrite(motorB_in1, LOW);
      digitalWrite(motorB_in2, HIGH);
      analogWrite(motorB_pwm, speed/2);  

      digitalWrite(motorC_in1, HIGH);
      digitalWrite(motorC_in2, LOW);
      analogWrite(motorC_pwm, speed); 

      digitalWrite(motorD_in1, LOW);
      digitalWrite(motorD_in2, HIGH);
      analogWrite(motorD_pwm, speed);  
}
void rotateright(int speed){
      digitalWrite(motorA_in1, HIGH);
      digitalWrite(motorA_in2, LOW);
      analogWrite(motorA_pwm, speed);  
  
      digitalWrite(motorB_in1, LOW);
      digitalWrite(motorB_in2, HIGH);
      analogWrite(motorB_pwm, speed/2); 

      digitalWrite(motorC_in1, HIGH);
      digitalWrite(motorC_in2, LOW);
      analogWrite(motorC_pwm, speed/2); 

      digitalWrite(motorD_in1, LOW);
      digitalWrite(motorD_in2, HIGH);
      analogWrite(motorD_pwm, speed);   
}
void rotateleft(int speed){
      digitalWrite(motorA_in1, HIGH);
      digitalWrite(motorA_in2, LOW);
      analogWrite(motorA_pwm, speed/2);  

      digitalWrite(motorB_in1, LOW);
      digitalWrite(motorB_in2, HIGH);
      analogWrite(motorB_pwm, speed);  

      digitalWrite(motorC_in1, HIGH);
      digitalWrite(motorC_in2, LOW);
      analogWrite(motorC_pwm, speed); 

      digitalWrite(motorD_in1, LOW);
      digitalWrite(motorD_in2, HIGH);
      analogWrite(motorD_pwm, speed/2); 
}
void yawleft(int speed){
      digitalWrite(motorA_in1, HIGH);
      digitalWrite(motorA_in2, LOW);
      analogWrite(motorA_pwm, speed/2); 


      digitalWrite(motorB_in1, LOW);
      digitalWrite(motorB_in2, HIGH);
      analogWrite(motorB_pwm, speed);  

      digitalWrite(motorC_in1, HIGH);
      digitalWrite(motorC_in2, LOW);
      analogWrite(motorC_pwm, speed/2); 

      digitalWrite(motorD_in1, LOW);
      digitalWrite(motorD_in2, HIGH);
      analogWrite(motorD_pwm, speed);  
}
void yawright(int speed){
      digitalWrite(motorA_in1, HIGH);
      digitalWrite(motorA_in2, LOW);
      analogWrite(motorA_pwm, speed);  

      digitalWrite(motorB_in1, LOW);
      digitalWrite(motorB_in2, HIGH);
      analogWrite(motorB_pwm, speed/2);  

      digitalWrite(motorC_in1, HIGH);
      digitalWrite(motorC_in2, LOW);
      analogWrite(motorC_pwm, speed); 

      digitalWrite(motorD_in1, LOW);
      digitalWrite(motorD_in2, HIGH);
      analogWrite(motorD_pwm, speed/2);  
}

void speedup(int &speed){
  if (speed<255){
    speed = speed + 5;
  }
}
void speeddown(int &speed){
  if (speed>0){
    speed = speed - 5;
  }
}
