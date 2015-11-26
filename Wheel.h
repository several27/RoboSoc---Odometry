//
// Created by Maciej Szpakowski on 13/11/15.
//

#ifndef ODOMETRY_WHEEL_H
#define ODOMETRY_WHEEL_H

#include "stdint.h"

class Wheel
{
public:
	Wheel();

	~Wheel();

	void setup(uint8_t, uint8_t, uint8_t, uint8_t, float);

	enum MoveDirection
	{
		FORWARD, BACKWARD
	};

	void setDirection(MoveDirection);
	enum MoveDirection getDirection();
	void move(MoveDirection, uint8_t);
	void move(uint8_t);

	void stop();

	uint8_t getCurrentSpeed();
	float getSpeedRatio();

	bool isOnHole();
	void updateDistance();
	uint16_t getDistance();

	static uint32_t convertMillimetersToSteps(uint32_t);

private:
	const uint16_t speedControlOnHoleAboveValue = 90;
	const static uint8_t wheelRadiusInMillimeters = 45;
	const static uint8_t numberOfStepsInWheel = 48;

	uint8_t speedControlPort;
	uint8_t directionControlPort1;
	uint8_t directionControlPort2;
	uint8_t speedSensorPort;

	float speedRatio;

	bool hole;
	uint16_t distancePassed;
	uint8_t currentSpeed = 0;

	uint8_t calculateSpeed(uint8_t);
};


#endif //ODOMETRY_WHEEL_H
