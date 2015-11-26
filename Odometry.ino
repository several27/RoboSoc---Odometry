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
  
  rightWheel.setup(ENB, IN3, IN4, IRB, 1);
  leftWheel.setup(ENA, IN1, IN2, IRA, 0.7826086957); // 0.75    0.7826086957
  robot.setup(&leftWheel, &rightWheel);
}


int val = 0;

int getLeftWheelSpeed(int rightWheelSpeed)
{
  // 90 / 115 - 0.7826086957
  // 90 / 114 - 0.7894736842
  return 0.75 * rightWheelSpeed;
}

void loop()
{ 
  if (Serial.available() > 0) 
  {
    // read the incoming byte:
    char function = Serial.read();
    Serial.available();Serial.available();Serial.available();
    Serial.print(Serial.read());Serial.print(Serial.read());Serial.print(Serial.read());
    int16_t param = (100 * (Serial.read() - '0')) + (10 * (Serial.read() - '0')) + (Serial.read() - '0');
    
    Serial.print(char(function));
    Serial.println(param);

    switch(function)
    {
      case 'w':
        robot.moveFor(Wheel::convertMillimetersToSteps(param), Wheel::FORWARD);
        break;
      case 'd':
        robot.turnRight(param);
        break;
      case 'a':
        robot.turnLeft(param);
        break;
    }
  }
  
//  Serial.println(analogRead(A3));
//    Serial.println(analogRead(A1));
//    delay(10);

//delay(5000);
////robot.moveFor(Wheel::convertMillimetersToSteps(326), Wheel::FORWARD);
//robot.turnRight(45);
//robot.stop();
//delay(5000);
//
//  delay(5000);
//  robot.spinInRight(75);
//  robot.stop();
//    
//  delay(5000);
////  robot.moveFor(250, Wheel::FORWARD);
//
//  Serial.println("robot.startSmoothly(255);");
//  robot.startSmoothly(255);
//
//  Serial.println("robot.moveFor(Wheel::convertMillimetersToSteps(326), Wheel::FORWARD);");
//  robot.moveFor(Wheel::convertMillimetersToSteps(326), Wheel::FORWARD);
//
//  Serial.println("robot.followCircleInRight(380, Wheel::convertMillimetersToSteps(233));");
//  robot.followCircleInRight(380, Wheel::convertMillimetersToSteps(233));
//
//  Serial.println("robot.followCircleInRight(300, Wheel::convertMillimetersToSteps(233));");
//  robot.followCircleInLeft(300, Wheel::convertMillimetersToSteps(233));

//  Serial.println("robot.followCircleInRight(360, Wheel::convertMillimetersToSteps(233));");
//  robot.followCircleInRight(360, Wheel::convertMillimetersToSteps(197));
//
//  Serial.println("robot.moveFor(Wheel::convertMillimetersToSteps(326), Wheel::FORWARD);");
//  robot.moveFor(Wheel::convertMillimetersToSteps(150), Wheel::FORWARD); // 150
//
//  Serial.println("robot.turnRight(45);");
//  robot.turnRight(45);
//
//  Serial.println("robot.moveFor(Wheel::convertMillimetersToSteps(257), Wheel::FORWARD);");
//  robot.moveFor(Wheel::convertMillimetersToSteps(257), Wheel::FORWARD);
//
//  Serial.println("robot.turnRight(53);");
//  robot.turnRight(53);
//
//  Serial.println("robot.moveFor(Wheel::convertMillimetersToSteps(650), Wheel::FORWARD);");
//  robot.moveFor(Wheel::convertMillimetersToSteps(650), Wheel::FORWARD);
  
//  robot.stop();
//  delay(5000);
//  
//  leftWheel.move(Wheel::FORWARD, 90);
//  rightWheel.move(Wheel::FORWARD, 114);  
//  delay(5000);
//  delay(5000);
//  delay(5000);

//  int speed = 200;
//
//  delay(5000);
//
//  for (int i = 0; i < speed; i++)
//  {
//    leftWheel.move(Wheel::FORWARD, getLeftWheelSpeed(i));
//    rightWheel.move(Wheel::FORWARD, i);  
//    delay(10);
//  }
//  
//  delay(1000);
//  leftWheel.move(Wheel::FORWARD, getLeftWheelSpeed(speed));
//  rightWheel.move(Wheel::FORWARD, speed);
////  delay(1000);
//
//  for (int i = speed; i > 0; i--)
//  { 
//    leftWheel.move(Wheel::FORWARD, getLeftWheelSpeed(i));
//    rightWheel.move(Wheel::FORWARD, i);  
//    delay(10);
    
//
//    unsigned long j = millis() + 100;
//
//    while (j > millis())
//    {
//      leftWheel->updateDistance();
//      rightWheel->updateDistance(); 
//    }
//  }
  
  
//  leftWheel.move(Wheel::FORWARD, 50);
//  delay(30);
//  leftWheel.move(Wheel::FORWARD, 85);
//  delay(5000);

   
//  for (int i = 0; i < this->normalSpeed; i++)
//  { 
//    leftWheel->move(Wheel::FORWARD, i);
//    rightWheel->move(Wheel::FORWARD, (i + 50) < 255 ? i + 50 : 255);  
//
//    unsigned long j = millis() + 100;
//
//    while (j > millis())
//    {
//      leftWheel->updateDistance();
//      rightWheel->updateDistance(); 
//    }
//  }
  









  
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
//  Serial.println(analogRead(A3));
//  Serial.print(" Right: ");
//  Serial.println(analogRead(A1));
//  Serial.println();

//  robot.moveFor(100, Wheel::FORWARD);
//  robot.stop();
//  delay(5000);

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
