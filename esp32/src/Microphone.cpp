#include "../Include/Sensors/Microphone.h"


/** 
 * @brief Construct a new Microphone::Microphone object 
 * 
 */
Microphone::Microphone() : values{0}, idx(0), read_stamp(0)
{
}


/**
 * @brief Set up the microphone pin and initialize the array with the first readings.
 * The array is initialized in order to avoid loud detection at boot.
 */
void Microphone::setup()
{
  pinMode(MIC_PIN, INPUT);
  for (int i = 0; i < DIM_MIC; i++) {
    values[i] = analogRead(MIC_PIN);
  }
}


/**
 * @brief Function used to compute average over DIM_MIC values read.
 * This function is used because we detect loudness looking to the deviation from the mean instead at
 * the value read directly. This is done to adapt to the noise environment.
 * @return the average of the last DIM_MIC values.
 * 
 */
float Microphone::computeAverage()
{
  float sum = 0;
  for (int i = 0; i < DIM_MIC; i++) {
    sum += values[i];
  }
  return sum / DIM_MIC;
}

/**
 * @brief Read microphone from input and store new values in the values array.
 * @return mew value read from the microphone every 50 milliseconds.
 */
int Microphone::readMic()
{
  if (millis() - read_stamp > 50) {
    read_stamp = millis();

    int new_value = analogRead(MIC_PIN);
    values[idx++] = new_value;
    if (idx == DIM_MIC) {
      idx = 0;
    }
    return analogRead(MIC_PIN);
  } else {
    return values[idx];
  }
}

