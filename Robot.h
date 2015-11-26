//
// Created by Maciej Szpakowski on 13/11/15.
//

#ifndef ODOMETRY_ROBOT_H
#define ODOMETRY_ROBOT_H

#include "stdint.h"
#include "Wheel.h"

class Robot
{
public:
	Robot();

	~Robot();

	void setup(Wheel *, Wheel *);

	void startSmoothly(uint8_t);

	void stop();
	void stopSmoothly();
	void stopSmoothly(uint8_t);

	void move(Wheel::MoveDirection);
	void moveForward();
	void moveBackward();
	void moveFor(uint16_t, Wheel::MoveDirection); // number of steps

  void spin(uint16_t, Wheel *, Wheel *);
  void spinInRight(uint16_t);
  void spinInLeft(uint16_t);

	void followCircle(uint16_t, uint32_t, Wheel *, Wheel *);
	void followCircleInLeft(uint16_t, uint32_t);
	void followCircleInRight(uint16_t, uint32_t);

	void turn(uint16_t, Wheel *, Wheel *);
	void turnLeft(uint16_t);
	void turnRight(uint16_t);

private:
	uint8_t normalSpeed = 255;
	const uint16_t width = 29; // 155 mm = 29 steps

	Wheel::MoveDirection lastMovementDirection = Wheel::FORWARD;

	Wheel *leftWheel;
	Wheel *rightWheel;

};


#endif //ODOMETRY_ROBOT_H
