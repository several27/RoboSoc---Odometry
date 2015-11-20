//
// Created by Maciej Szpakowski on 13/11/15.
//

#include "Arduino.h"
#include "Robot.h"

Robot::Robot() { }
Robot::~Robot() { }

void Robot::setup(Wheel* leftWheel, Wheel* rightWheel)
{
	this->leftWheel = leftWheel;
	this->rightWheel = rightWheel;
}

void Robot::stop()
{
//  Wheel::MoveDirection oppositeDirection;
//  switch (this->lastMovementDirection)
//  {
//    case Wheel::FORWARD:
//      this->move(Wheel::BACKWARD);
//      break;
//    case Wheel::BACKWARD:
//      this->move(Wheel::FORWARD);
//      break;
//  }
//
//  delay(45);
  
  this->leftWheel->stop();
  this->rightWheel->stop();
}

void Robot::move(Wheel::MoveDirection direction)
{
  this->lastMovementDirection = direction;
  
	this->leftWheel->move(direction, this->normalSpeed);
	this->rightWheel->move(direction, this->normalSpeed);
}

void Robot::moveForward()
{
	this->move(Wheel::FORWARD);
}

void Robot::moveBackward()
{
	this->move(Wheel::BACKWARD);
}

void Robot::moveFor(uint16_t steps, Wheel::MoveDirection direction)
{
	this->move(direction);

  uint16_t stepsMadeByRightWheel = 0;
  uint16_t stepsMadeByLeftWheel = 0;
	
	while ( (stepsMadeByRightWheel + stepsMadeByLeftWheel) < (steps * 2) )
	{ 
    stepsMadeByLeftWheel += this->leftWheel->getDistance();
    this->leftWheel->updateDistance();

    if (stepsMadeByLeftWheel >= steps) // -13
    {
//      this->stop();
    }
      
    stepsMadeByRightWheel += this->rightWheel->getDistance();
    this->rightWheel->updateDistance();
    
    if (stepsMadeByRightWheel >= (steps))
    {
//      this->stop();
//      this->rightWheel->move(Wheel::BACKWARD, 200);
    }

//    Serial.print("left: ");
//    Serial.print(stepsMadeByLeftWheel);
//    Serial.print(",");
//    Serial.print(analogRead(A0));
//    Serial.print("   right: ");
//    Serial.print(stepsMadeByRightWheel);
//    Serial.print(",");
//    Serial.print(analogRead(A1));
//    Serial.println("");
	}

  this->stop();

//  while (stepsMadeByRightWheel < steps)
//  { 
//    stepsMadeByRightWheel += this->rightWheel->getDistance();
//    this->rightWheel->updateDistance();
//    
//    if (stepsMadeByRightWheel >= steps)
//      this->rightWheel->stop();
//
//    Serial.print("   right: ");
//    Serial.print(stepsMadeByRightWheel);
//    Serial.print(",");
//    Serial.print(analogRead(A1));
//    Serial.println("");
//  }

//  while (steps > 0)
//  {
//    steps -= this->rightWheel->getDistance();
//    this->rightWheel->updateDistance();
//    Serial.println(steps);
//  }
}

// (uint16_t) angle is an angle of a circle to follow
// (uint32_t) radius of a bigger circle that is followed by the firstWheel
// secondWheel follows the smaller circle which is calculated
// by substracting width of an robot from bigger radius
void Robot::followCircle(uint16_t angle, uint32_t radius, Wheel* firstWheel, Wheel* secondWheel)
{
	uint16_t stepsOfFirstCircle = 2 * PI * (radius - this->width) * angle / 360;
	uint16_t stepsOfSecondCircle = 2 * PI * radius * angle / 360;
	
	uint8_t secondWheelSpeed = stepsOfSecondCircle * this->normalSpeed / stepsOfFirstCircle;
//  Serial.println(this->normalSpeed);
//  Serial.println(secondWheelSpeed);
  
	firstWheel->move(Wheel::FORWARD, secondWheelSpeed);
	secondWheel->move(Wheel::FORWARD, this->normalSpeed);
	
  while (stepsOfFirstCircle + stepsOfSecondCircle > 0)
  { 
    stepsOfFirstCircle -= firstWheel->getDistance();
    firstWheel->updateDistance();
  
    if (stepsOfFirstCircle <= 0)
    {
      firstWheel->stop();
    }
//    Serial.println(firstWheel->getDistance());
      
    stepsOfSecondCircle -= secondWheel->getDistance();
    secondWheel->updateDistance();
  
    if (stepsOfSecondCircle <= 0)
    {
      secondWheel->stop();
    }
//    Serial.println(secondWheel->getDistance());
  }

  this->stop();
}

// follows a circle in the right direction, bigger distance will be driven
// by the left wheel
void Robot::followCircleInRight(uint16_t angle, uint32_t radius)
{
	this->followCircle(angle, radius, this->rightWheel, this->leftWheel);
}

// follows a circle in the left direction, bigger distance will be driven
// by the right wheel
void Robot::followCircleInLeft(uint16_t angle, uint32_t radius)
{
	this->followCircle(angle, radius, this->leftWheel, this->rightWheel);
}

// Moves the firstWheel and stops the secondWheel
// as long as angle is reached
void Robot::turn(uint16_t angle, Wheel* firstWheel, Wheel* secondWheel)
{
	Robot::followCircle(angle, this->width + 1, firstWheel, secondWheel);
}

void Robot::turnRight(uint16_t angle)
{
	this->turn(angle, this->rightWheel, this->leftWheel);
}

void Robot::turnLeft(uint16_t angle)
{
	this->turn(angle, this->leftWheel, this->rightWheel);
}
