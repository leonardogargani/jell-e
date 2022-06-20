#ifndef LEDSTRIP_H
#define LEDSTRIP_H

#include "FastLED.h"
#include "../Pins.h"

#define NUM_LEDS 10
#define BRIGHTNESS 64


/**
 * @brief Class for the addressable LED strip with its operatings
 *
 */
class LEDStrip
{
private:
  CRGB leds[NUM_LEDS];      // LED vector
  float breath_intensity;    // Store the brightness of the breath
  uint8_t breath_counter;    // Counter of the breath used to change the intensity of the LED
  float smoothness_pts;     // Larger value, slower change in brightness
  float theta;              // Affects the width of peak (more or less darkness) of the Gaussian function
  float beta;               // Shifts the Gaussian function to be symmetric
  unsigned long last_update; // Last update of the breath function

public:
  LEDStrip();
  void setup();
  void angry();
  void sad();
  void scared();
  void happy();
  void hello();
  void breath();
  void reset();
};

#endif
