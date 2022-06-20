#ifndef MICROPHONE_H
#define MICROPHONE_H

#include "Arduino.h"
#include "../Pins.h"

#define DIM_MIC 50
#define DELTA 100
#define LOUD 400


/**
 * @brief Class that define the Microphone.
 * 
 */ 
class Microphone
{
private:
  int values[DIM_MIC]; //Array that store microphone values read, used to compute the average.
  int idx; //Index to iterate over the values array.
  bool read_stamp; //Store timestamp of the last microphone lecture. Used to wait 50 milliseconds from one read and the other.

public:
  Microphone();
  void setup();
  float computeAverage();
  int readMic();
};

#endif
