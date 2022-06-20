#ifndef ULTRA_SENSOR_H
#define ULTRA_SENSOR_H

#include "Arduino.h"
#include "../Pins.h"

#define DELTA_DISTANCE 20
#define MIN_DISTANCE 20
#define MAX_DISTANCE 200
#define MIN_SWING 4


/**
 * @brief Class that define the Ultrasonic Sensor.
 */
class UltrasonicSensor
{
private:
  long duration; //Store the time of flight of the signal.
  int swing_counter; //Store the number of swing detected.
  int previous_distance; //Store the previous distance.
  long int last_update; //Timestamp of the last swing detected. Used to debounce the swing_counter update and avoid false-positive.

public:
  UltrasonicSensor();
  void setup();
  int readDistance();
  int getSwingCounter();
  void resetSwingCounter();
  void updateSwingCounter(int distance);
};

#endif