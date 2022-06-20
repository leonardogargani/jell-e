#ifndef TENTACLE_H
#define TENTACLE_H

#include "Arduino.h"
#include "ServoEasing.h"
#include "../Pins.h"


/**
 * @brief Class representing the tentacle and its operations thanks to the use of the two servo motors
 *
 */
class Tentacle
{
private:
  ServoEasing servo_hor;
  ServoEasing servo_vert;

  ServoEasing *servo_hor_ptr;
  ServoEasing *servo_vert_ptr;

  int velocity;             // Velocity of the servo motors
  unsigned long start_time; // Initial time of the movement of the servo motors
  bool servos_in_use;       // Tell if the servo motor is moving

public:
  Tentacle();
  void setup();
  void moveRandomly();
  void sayHi();
  void curious();
  void scared();
  void angry();
  void sad();
  void happy();
  void comeOn();
  void reset();
};

#endif
