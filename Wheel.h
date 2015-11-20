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
	
	void setup(uint8_t, uint8_t, uint8_t, uint8_t);
	
	enum MoveDirection {FORWARD, BACKWARD};
	void setDirection(MoveDirection);
	enum MoveDirection getDirection();
	
	void move(MoveDirection, uint8_t);
	void move(uint8_t);
	void stop();

  bool isOnHole(void);
  void updateDistance(void);
  uint16_t getDistance();

  static uint32_t convertMilimitersToSteps(uint32_t);

private:
    // TODO: What is this value ??
    const uint16_t speedControlOnHoleAboveValue = 100;
    const static uint8_t wheelRadiusInMilimiters = 45;
    const static uint8_t numberOfStepsInWheel = 48;
    
    uint8_t speedControlPort;
    uint8_t directionControlPort1;
    uint8_t directionControlPort2;
    uint8_t speedSensorPort;
    
    bool hole;
    uint16_t distancePassed;
};


#endif //ODOMETRY_WHEEL_H
