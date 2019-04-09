#include <UCMotor.h>
UC_DCMotor leftMotor1(3, MOTOR34_64KHZ);
UC_DCMotor rightMotor1(4, MOTOR34_64KHZ);
UC_DCMotor leftMotor2(1, MOTOR34_64KHZ);
UC_DCMotor rightMotor2(2, MOTOR34_64KHZ);

#include <Ultrasonic.h>
Ultrasonic ultrasonic(A2, A3);

const int LIGHT_PIN_RIGHT = A5;
const int LIGHT_PIN_LEFT = A4;
unsigned int offset_right = 0;
unsigned int offset_left = 0;

void setup() {

  Serial.begin(9600);
  
  pinMode(LIGHT_PIN_RIGHT, INPUT);
  pinMode(LIGHT_PIN_LEFT, INPUT);

  for (int i=0; i<100; i++){
      offset_right += analogRead(LIGHT_PIN_RIGHT);
      offset_left += analogRead(LIGHT_PIN_LEFT);
      delay(20);
  }
  offset_right = offset_right/100;
  offset_left = offset_left/100;
}

void loop() {
  int Light_right = analogRead(LIGHT_PIN_RIGHT)-offset_right;
  int Light_left = analogRead(LIGHT_PIN_LEFT)-offset_left;

  int diff = Light_right-Light_left;
  //positiv: snu til højre
  //negativ: snu til venstre
  
  int  dist = ultrasonic.distanceRead();

  if (Light_right<10 && Light_left<10){  //not enough light
      brake();
    }
    
  else if (dist<40){
      brake();
    }
    
  else if (diff<10 && diff>-10){
      forward();
    }
    
  else if (diff < -10){
      turn_left();
    }
    
  else if (diff > 10){
      turn_right();
    }
  
  /*
  Serial.print("Right sensor: "); Serial.println(Light_right);
  Serial.print("Left sensor: "); Serial.println(Light_left);
  Serial.println("");
  */
  
  delay(50);
}

void forward(){
    //Forward
      leftMotor1.run(0x01); rightMotor1.run(0x01);
      leftMotor2.run(0x01); rightMotor2.run(0x01);
      leftMotor1.setSpeed(200); rightMotor1.setSpeed(200);
      leftMotor2.setSpeed(200); rightMotor2.setSpeed(200);  
  }
      
void turn_left(){
  //left
    leftMotor1.run(0x01); rightMotor1.run(0x01);
    leftMotor2.run(0x01); rightMotor2.run(0x01);
    leftMotor1.setSpeed(0); rightMotor1.setSpeed(200);
    leftMotor2.setSpeed(0); rightMotor2.setSpeed(200);  
  }
  
void turn_right(){
    //right
    leftMotor1.run(0x01); rightMotor1.run(0x01);
    leftMotor2.run(0x01); rightMotor2.run(0x01);
    leftMotor1.setSpeed(200); rightMotor1.setSpeed(0);
    leftMotor2.setSpeed(200); rightMotor2.setSpeed(0); 
  }  

  void brake(){
    //brake
    leftMotor1.run(0x01); rightMotor1.run(0x01);
    leftMotor2.run(0x01); rightMotor2.run(0x01);
    leftMotor1.setSpeed(0); rightMotor1.setSpeed(0);
    leftMotor2.setSpeed(0); rightMotor2.setSpeed(0);      
  }
