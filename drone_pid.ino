#include <Wire.h>
#include <MPU6050.h>

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

MPU6050 mpu;

float integral = 0;
float pre = 0;
float target = 10;
float kp = 1;
float ki = 0.1;
float kd = 0.01;

float integralroll = 0;
float preroll = 0;
float targetroll = 10;
float kpr = 1;
float kir = 0.1;
float kdr = 0.01;

float integralyaw = 0;
float preyaw = 0;
float targetyaw = 10;
float kpy = 1;
float kiy = 0.1;
float kdy = 0.01;

int speed = 230;

void setup(){
  Serial.begin(115200);
  Wire.begin();
  mpu.initialize();
  
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

  if(!mpu.testConnection()){
    Serial.println("Mpu failed");
    while(1);
  }
}

void loop(){
  int16_t x,y,z;
  int16_t gx, gy, gz;

  mpu.getAcceleration(&x,&y,&z);
  mpu.getRotation(&gx,&gy,&gz);

  float ax = x/16384.0;
  float ay = y/16384.0;
  float az = z/16384.0;

  float gyroX = gx/131.0;
  float gyroY = gy/131.0;
  float gyroZ = gz/131.0;

  float roll = atan2(ay,az)*180/PI;
  float pitch = atan2(-ax,sqrt(ay*ay+az*az))*180/PI;
  float yaw = gyroZ*0.001;

  float error = target - pitch;
  float errorroll = targetroll - roll;
  float erroryaw = targetyaw - yaw;

  integral += error;
  if(integral>100){
    integral = 100;
  }
  else if(integral<-100){
    integral = -100;
  }

  integralroll += errorroll;
  if(integralroll>100){
    integralroll = 100;
  }
  else if(integralroll<-100){
    integralroll = -100;
  }

  integralyaw += erroryaw;
  if(integralyaw>100){
    integralyaw = 100;
  }
  else if(integralyaw<-100){
    integralyaw = -100;
  }

  float derivative = error - pre;
  float derivativeroll = errorroll - preroll;
  float derivativeyaw = erroryaw - preyaw;

  float pd = kp*error + ki*integral + kd*derivative;
  float pdroll = kpr*errorroll + kir*integralroll + kdr*derivativeroll;
  float pdyaw = kpy*erroryaw + kiy*integralyaw + kdy*derivativeyaw;

  pre = error;
  preroll = errorroll; 
  preyaw = erroryaw;

  if(pd>0){
    pitchforward(constrain(speed+pd,0,255));
  }
  else if(pd<0){
    pitchbackward(constrain(speed+abs(pd),0,255));
  }

  if(pdroll>0){
    rollright(constrain(speed+pdroll,0,255));
  }
  else if(pdroll<0){
    rollleft(constrain(speed+abs(pdroll),0,255));
  }
  if(pdyaw>0){
    yawright(constrain(speed+pdyaw,0,255));
  }
  else if(pdyaw<0){
    yawleft(constrain(speed+abs(pdyaw),0,255));
  }
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

void rollright(int speed){
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

void rollleft(int speed){
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
