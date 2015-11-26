//
// Created by Maciej Szpakowski on 13/11/15.
//

#include "Arduino.h"
#include "Wheel.h"

Wheel::Wheel()
{ }

Wheel::~Wheel()
{ }

void Wheel::setup(uint8_t speedControlPort, uint8_t directionControlPort1, uint8_t directionControlPort2,
                  uint8_t speedSensorPort, float speedRatio)
{
	this->speedControlPort = speedControlPort;
	this->directionControlPort1 = directionControlPort1;
	this->directionControlPort2 = directionControlPort2;
	this->speedSensorPort = speedSensorPort;

	this->speedRatio = speedRatio;

	pinMode(speedControlPort, OUTPUT);
	pinMode(directionControlPort1, OUTPUT);
	pinMode(directionControlPort2, OUTPUT);

	this->distancePassed = 0;
	this->hole = this->isOnHole();

	this->setDirection(Wheel::FORWARD);
}

uint8_t Wheel::calculateSpeed(uint8_t speed)
{
	return this->speedRatio * speed;
}

void Wheel::setDirection(MoveDirection direction)
{
	switch (direction)
	{
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
	this->setDirection(direction);
	this->move(speed);
}

void Wheel::move(uint8_t speed)
{
	this->currentSpeed = this->calculateSpeed(speed);
	analogWrite(this->speedControlPort, this->currentSpeed);
}

void Wheel::stop()
{
	this->move(0);
}

uint8_t Wheel::getCurrentSpeed()
{
	return this->currentSpeed;
}

float Wheel::getSpeedRatio()
{
	return this->speedRatio;
}

bool Wheel::isOnHole()
{
	return analogRead(this->speedSensorPort) >= this->speedControlOnHoleAboveValue;
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

uint32_t Wheel::convertMillimetersToSteps(uint32_t millimeters)
{
	return millimeters * numberOfStepsInWheel / 2 / PI / wheelRadiusInMillimeters;
}

