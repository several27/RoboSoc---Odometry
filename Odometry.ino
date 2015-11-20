#include "stdint.h"
#include "Wheel.h"
#include "Robot.h"

// Left Wheel Ports
uint8_t ENA = 10;
uint8_t IN1 = 9;
uint8_t IN2 = 8;
uint8_t IRA = A3;

// Right Wheel Ports
uint8_t IN3 = 7;   
uint8_t IN4 = 6;  
uint8_t ENB = 5;
uint8_t IRB = A1;

Wheel leftWheel;
Wheel rightWheel;
Robot robot;

void setup()
{
  Serial.begin(9600);
  
  rightWheel.setup(ENB, IN3, IN4, IRB);
  leftWheel.setup(ENA, IN1, IN2, IRA);
  robot.setup(&leftWheel, &rightWheel);
}


int val = 0;

void loop()
{
//  char buffer[50];
//  sprintf(buffer, "Left: %d Right: %d", analogRead(IRA), analogRead(IRB));
//  Serial.println(analogRead(IRA));
//  Serial.println(analogRead(IRB));
//  
//  delay(100);
  
//  leftWheel.move(Wheel::FORWARD, 200);
//  rightWheel.move(Wheel::BACKWARD, 50);
  
//  digitalWrite(12, HIGH);

//  rightWheel.move(Wheel::FORWARD, 50);
//  val = analogRead(IRB);
//  Serial.println(val);
//  delay(100);

//  robot.move(Wheel::BACKWARD);
//robot.moveFor(Wheel::convertMilimitersToSteps(200), Wheel::FORWARD);
//robot.moveFor(3, Wheel::BACKWARD);
//robot.moveFor(100, Wheel::BACKWARD);
//robot.moveFor(100, Wheel::FORWARD);
//robot.stop();
//delay(5000);

//  val = analogRead(IR_LED_PIN);
//  
//  if (val < 200){
//    Serial.print("L\n");
//  }
//  else{
//    Serial.print("H\n");
//  }
  
//  rightWheel.stop();
//  leftWheel.stop();
//  delay(3000);
//  rightWheel.move(Wheel::FORWARD, 200);
//  delay(3000);
//  rightWheel.move(Wheel::BACKWARD, 200);
//  delay(3000);
//  rightWheel.stop();
//  leftWheel.move(Wheel::FORWARD, 200);
//  delay(3000);
//  leftWheel.move(Wheel::BACKWARD, 200);
//  delay(3000);

//  robot.moveForward();

//  robot.turnLeft(32);
//  robot.moveFor(Wheel::convertMilimitersToSteps(200), Wheel::FORWARD);
//  robot.followCircleInRight(180, Wheel::convertMilimitersToSteps(100));
//  uint16_t steps = 2 * PI * 300 * 180 / 360 ;
//  Serial.println(steps);

 
//  robot.followCircleInRight(180, Wheel::convertMilimitersToSteps(233));
//  robot.stop();
//  delay(5000);
//  
//  robot.followCircleInLeft(180, Wheel::convertMilimitersToSteps(233));
//  robot.stop();
//  delay(5000);

//

//leftWheel.move(255);
//
//  Serial.print("Left: ");
//  Serial.print(analogRead(A3));
//  Serial.print(" Right: ");
//  Serial.print(analogRead(A1));
//  Serial.println();

  robot.moveFor(100, Wheel::FORWARD);
//  robot.stop();
  delay(5000);

//  robot.turnRight(60);
//  robot.stop();
//  delay(1000);
//
//  robot.turnRight(60);
//  robot.stop();
//  delay(1000);
//
//  robot.moveFor(Wheel::convertMilimitersToSteps(100), Wheel::FORWARD);
//  robot.stop();
//  delay(1000);
//  
//  robot.followCircleInRight(180, Wheel::convertMilimitersToSteps(233));
//  robot.stop();
//  delay(1000);
//
//  robot.followCircleInRight(180, Wheel::convertMilimitersToSteps(233));
//  robot.stop();
//  delay(1000);
//  
//  robot.followCircleInLeft(180, Wheel::convertMilimitersToSteps(233));
//  robot.stop();
//  delay(1000);
//  
//  robot.followCircleInRight(180, Wheel::convertMilimitersToSteps(197));
//  robot.stop();
//  delay(1000);
//  
//  robot.moveFor(Wheel::convertMilimitersToSteps(300), Wheel::FORWARD);
//  robot.stop();
//  delay(1000);
//
//  robot.turnRight(45);
//  robot.stop();
//  delay(1000);
//
//  robot.moveFor(Wheel::convertMilimitersToSteps(257), Wheel::FORWARD);
//  robot.stop();
//  delay(1000);
//
//  robot.turnRight(53);
//  robot.stop();
//  delay(1000);
//
//  robot.moveFor(Wheel::convertMilimitersToSteps(650), Wheel::FORWARD);
//  robot.stop();
//  delay(1000);

//  robot.moveFor(96, Wheel::FORWARD);
//
////  robot.followCircleInRight(180, Wheel::convertMilimitersToSteps(233));
////  robot.stop();
//  delay(10000);

//  rightWheel.move(Wheel::FORWARD, 200);
//  Serial.println(analogRead(A1));
//  delay();
}
