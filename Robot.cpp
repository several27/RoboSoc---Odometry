//
// Created by Maciej Szpakowski on 13/11/15.
//

#include "Arduino.h"
#include "Robot.h"

Robot::Robot()
{ }

Robot::~Robot()
{ }

void Robot::setup(Wheel *leftWheel, Wheel *rightWheel)
{
	this->leftWheel = leftWheel;
	this->rightWheel = rightWheel;
}

void Robot::startSmoothly(uint8_t speed)
{
	for (uint8_t i = 0; i < speed; i++)
	{
		leftWheel->move(i);
		rightWheel->move(i);
    
    unsigned long j = millis() + 5;

    while (j > millis())
    {
      leftWheel->updateDistance();
      rightWheel->updateDistance(); 
    }
	}
}

void Robot::stop()
{
	this->leftWheel->stop();
	this->rightWheel->stop();
}

void Robot::stopSmoothly()
{
	uint8_t leftWheelSpeed = this->leftWheel->getCurrentSpeed(),
			rightWheelSpeed = this->rightWheel->getCurrentSpeed();

	while (this->leftWheel->getCurrentSpeed() + this->rightWheel->getCurrentSpeed() > 0)
	{
		leftWheelSpeed--;
		rightWheelSpeed--;

		this->leftWheel->move(leftWheelSpeed);
		this->rightWheel->move(rightWheelSpeed);

		delay(5);
	}
}

void Robot::stopSmoothly(uint8_t speed)
{
	for (uint8_t i = speed; i > 0; i--)
	{
		this->leftWheel->move(Wheel::FORWARD, i);
		this->rightWheel->move(Wheel::FORWARD, i);

		delay(10);
	}
}

void Robot::move(Wheel::MoveDirection direction)
{
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
  uint16_t madeSteps = 0;
  uint8_t speed = 0;

  // Start
  while (speed < this->normalSpeed)
  {
    leftWheel->move(speed);
    rightWheel->move(speed);

    if (madeSteps >= steps)
    {
      break;
    }
    
    unsigned long j = millis() + 5;

    while (j > millis())
    {
      leftWheel->updateDistance();
      rightWheel->updateDistance(); 

      madeSteps += leftWheel->getDistance() + rightWheel->getDistance();
    }

    speed++;
  }
  
  uint16_t stepsToAccelerate = madeSteps;

  // Middle
  if (madeSteps < steps)
  {
    while (madeSteps < (steps * 2) - stepsToAccelerate)
    {
      leftWheel->updateDistance();
      rightWheel->updateDistance(); 
  
      madeSteps += leftWheel->getDistance() + rightWheel->getDistance();
    }
  }
  
  // End
  for (uint8_t i = speed; i > 0; i--)
  {
    this->leftWheel->move(Wheel::FORWARD, i);
    this->rightWheel->move(Wheel::FORWARD, i);

    delay(5);
  }
}

void Robot::spin(uint16_t angle, Wheel *firstWheel, Wheel *secondWheel)
{
  uint16_t steps = (PI * this->width * angle / 360) * 4;
  uint8_t speed = 0;

  firstWheel->move(Wheel::FORWARD, 0);
  secondWheel->move(Wheel::BACKWARD, 0);

  Serial.println(steps);

  while (steps > 0)
  {
    firstWheel->move(Wheel::FORWARD, speed);
    secondWheel->move(Wheel::BACKWARD, speed);

    if (speed < 255)
      speed++;

    unsigned long j = millis() + 10;
    while (j > millis())
    {
      if (steps > 0)
      {
        steps -= firstWheel->getDistance();
        firstWheel->updateDistance();
      }

      if (steps > 0)
      {
        steps -= secondWheel->getDistance();
        secondWheel->updateDistance(); 
      }
    }
  }
}

void Robot::spinInRight(uint16_t angle)
{
  this->spin(angle, this->leftWheel, this->rightWheel);
}

void Robot::spinInLeft(uint16_t angle)
{
  this->spin(angle, this->rightWheel, this->leftWheel);
}

// (uint16_t) angle is an angle of a circle to follow
// (uint32_t) radius of a bigger circle that is followed by the firstWheel
// secondWheel follows the smaller circle which is calculated
// by subtracting width of an robot from bigger radius
void Robot::followCircle(uint16_t angle, uint32_t radius, Wheel *firstWheel, Wheel *secondWheel)
{
	uint16_t stepsOfFirstCircle = (2 * PI * radius * angle / 360);
	uint16_t stepsOfSecondCircle = (2 * PI * (radius - this->width) * angle / 360);
  uint16_t steps = stepsOfFirstCircle + stepsOfSecondCircle;

	uint8_t secondWheelSpeed = stepsOfSecondCircle * this->normalSpeed / stepsOfFirstCircle;

  uint8_t madeSteps = 0, currentFirstWheelSpeed = 0, currentSecondWheelSpeed = 0;
//
//  Serial.println(stepsOfFirstCircle);
//  Serial.println(stepsOfSecondCircle);
//  Serial.println(steps);
//  

//	firstWheel->move(Wheel::FORWARD, this->normalSpeed);
//	secondWheel->move(Wheel::FORWARD, secondWheelSpeed);

  // Start
  while (currentFirstWheelSpeed < this->normalSpeed || currentSecondWheelSpeed < secondWheelSpeed)
  {
    firstWheel->move(currentFirstWheelSpeed);
    secondWheel->move(currentSecondWheelSpeed);

    if (madeSteps >= steps)
    {
      break;
    }
    
    unsigned long j = millis() + 5;

    while (j > millis())
    {
      leftWheel->updateDistance();
      rightWheel->updateDistance(); 

      madeSteps += leftWheel->getDistance() + rightWheel->getDistance();
    }

    if (currentFirstWheelSpeed < this->normalSpeed)
      currentFirstWheelSpeed++;

    if (currentSecondWheelSpeed < secondWheelSpeed)
      currentSecondWheelSpeed++;
  }
  
  uint16_t stepsToAccelerate = madeSteps;

  // Middle
  if (madeSteps < steps)
  {
    while (madeSteps < (steps * 2) - stepsToAccelerate)
    {
      leftWheel->updateDistance();
      rightWheel->updateDistance(); 
  
      madeSteps += leftWheel->getDistance() + rightWheel->getDistance();
    }
  }
  
  // End
  while (currentFirstWheelSpeed > 0 || currentSecondWheelSpeed > 0)
  {
    firstWheel->move(Wheel::FORWARD, currentFirstWheelSpeed);
    secondWheel->move(Wheel::FORWARD, currentSecondWheelSpeed);
//Serial.println(currentFirstWheelSpeed);
    delay(5);

    if (currentFirstWheelSpeed > 0)
      currentFirstWheelSpeed--;

    if (currentSecondWheelSpeed > 0)
      currentSecondWheelSpeed--;
  }

}

// follows a circle in the right direction, bigger distance will be driven
// by the left wheel
void Robot::followCircleInRight(uint16_t angle, uint32_t radius)
{
	this->followCircle(angle, radius, this->leftWheel, this->rightWheel);
}

// follows a circle in the left direction, bigger distance will be driven
// by the right wheel
void Robot::followCircleInLeft(uint16_t angle, uint32_t radius)
{
	this->followCircle(angle, radius, this->rightWheel, this->leftWheel);
}

// Moves the firstWheel and stops the secondWheel
// as long as angle is reached
void Robot::turn(uint16_t angle, Wheel *firstWheel, Wheel *secondWheel)
{
	uint16_t madeSteps = 0;
  uint8_t speed = 0;

  uint16_t steps = (2 * PI * this->width * angle / 360);

  // Start
  while (speed < this->normalSpeed)
  {
    firstWheel->move(speed);

    if (madeSteps >= steps / 2)
    {
      break;
    }
    
    unsigned long j = millis() + 5;

    while (j > millis())
    {
      leftWheel->updateDistance();

      madeSteps += leftWheel->getDistance();
    }

    speed++;
  }
  
  uint16_t stepsToAccelerate = madeSteps;

  // Middle
  if (madeSteps < steps / 2)
  {
    while (madeSteps < (steps * 2) - stepsToAccelerate)
    {
      firstWheel->updateDistance();
  
      madeSteps += firstWheel->getDistance();
    }
  }
  
  // End
  for (uint8_t i = speed; i > 0; i--)
  {
    firstWheel->move(Wheel::FORWARD, i);

    delay(5);
  }
}

void Robot::turnRight(uint16_t angle)
{
	this->turn(angle, this->leftWheel, this->rightWheel);
}

void Robot::turnLeft(uint16_t angle)
{
	this->turn(angle, this->rightWheel, this->leftWheel);
}
