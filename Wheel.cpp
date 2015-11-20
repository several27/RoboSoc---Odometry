//
// Created by Maciej Szpakowski on 13/11/15.
//

#include "Arduino.h"
#include "Wheel.h"

Wheel::Wheel() { }

Wheel::~Wheel() { }

void Wheel::setup(uint8_t speedControlPort, uint8_t directionControlPort1, uint8_t directionControlPort2, uint8_t speedSensorPort)
{
	this->speedControlPort = speedControlPort;
	this->directionControlPort1 = directionControlPort1;
	this->directionControlPort2 = directionControlPort2;
	this->speedSensorPort = speedSensorPort;
	
	pinMode(speedControlPort, OUTPUT);
	pinMode(directionControlPort1, OUTPUT);
	pinMode(directionControlPort2, OUTPUT);
//	pinMode(speedSensorPort, OUTPUT);
	
	this->distancePassed = 0;
	this->hole = this->isOnHole();
}


void Wheel::setDirection(MoveDirection direction)
{
	switch (direction)
	{ // TODO: are directions correct ?
		case FORWARD:
			digitalWrite(this->directionControlPort1, HIGH);
			digitalWrite(this->directionControlPort2, LOW);
			break;
		case BACKWARD:
			digitalWrite(this->directionControlPort1, LOW);
			digitalWrite(this->directionControlPort2, HIGH);
			break;
	}
}

enum Wheel::MoveDirection Wheel::getDirection()
{
	return Wheel::FORWARD;
};

void Wheel::move(MoveDirection direction, uint8_t speed)
{
	setDirection(direction);
	this->move(speed);
}

void Wheel::move(uint8_t speed)
{
	analogWrite(speedControlPort, speed);
}

void Wheel::stop()
{
	this->move(0);
}

bool Wheel::isOnHole()
{
//    Serial.println(analogRead(this->speedSensorPort));
    return analogRead(this->speedSensorPort) >= this->speedControlOnHoleAboveValue; // TODO: ???
}

void Wheel::updateDistance()
{
	if (hole != this->isOnHole())
	{
		this->distancePassed++;
    hole = this->isOnHole();
	}
}

uint16_t Wheel::getDistance()
{
	uint16_t distancePassed = this->distancePassed;
	this->distancePassed = 0;
	return distancePassed;
}

uint32_t Wheel::convertMilimitersToSteps(uint32_t milimiters)
{
  return milimiters * numberOfStepsInWheel / 2 / PI / wheelRadiusInMilimiters;
}

