#include "../Include/Actuators/LEDStrip.h"


/**
 * @brief Construct a new LEDStrip::LEDStrip object
 *
 */
LEDStrip::LEDStrip() : breath_intensity(0), breath_counter(0), smoothness_pts(260), theta(0.15), beta(0.5)
{
}


/**
 * @brief Initial setup of the LEDStrip: set number of LEDs used and LEDs brightness
 *
 */
void LEDStrip::setup()
{
  FastLED.addLeds<NEOPIXEL, LED_PIN>(leds, NUM_LEDS);
  FastLED.setBrightness(BRIGHTNESS);
}


/**
 * @brief Function for the angry gesture: all the LEDs become red
 *
 */
void LEDStrip::angry()
{
  for (int i = 1; i < NUM_LEDS; i++) {
    leds[i] = CRGB::Red;
  }
  FastLED.show();
}


/**
 * @brief Function for the sad gesture: all the LEDs become blue
 *
 */
void LEDStrip::sad()
{
  for (int i = 1; i < NUM_LEDS; i++) {
    leds[i] = CRGB::Navy;
  }
  FastLED.show();
}


/**
 * @brief Function for the scared gesture: all the LEDs become purple
 *
 */
void LEDStrip::scared()
{
  for (int i = 1; i < NUM_LEDS; i++) {
    leds[i] = CRGB::Purple;
  }
  FastLED.show();
}


/**
 * @brief Function for the happy gesture: each LED has a different color from each other
 *
 */
void LEDStrip::happy()
{
  for (int i = 1; i < NUM_LEDS; i++) {
    switch (i % 9)
    {
    case 0:
      leds[i] = CRGB::Purple;
      break;
    case 1:
      leds[i] = CRGB::Gold;
      break;
    case 2:
      leds[i] = CRGB::Blue;
      break;
    case 3:
      leds[i] = CRGB::Red;
      break;
    case 4:
      leds[i] = CRGB::Green;
      break;
    case 5:
      leds[i] = CRGB::HotPink;
      break;
    case 6:
      leds[i] = CRGB::Brown;
      break;
    case 7:
      leds[i] = CRGB::White;
      break;
    case 8:
      leds[i] = CRGB::Orange;
      break;

    }
  }
  FastLED.show();
}


/**
 * @brief Function for the hello gesture: all the LEDs become green
 *
 */
void LEDStrip::hello()
{
  for (int i = 1; i < NUM_LEDS; i++) {
    leds[i] = CRGB::Green;
  }
  FastLED.show();
}


/**
 * @brief Function for the breath gesture: all the LEDs become white and change their intensity from low to high and viceversa
 * thanks to the Gaussian function
 *
 */
void LEDStrip::breath()
{
  unsigned long timestamp = millis();
  if (timestamp - last_update > 25) {
    // Condition for changing the intensity of the LED using a Gaussian function
    if (breath_counter < smoothness_pts) {
      breath_intensity = 200.0 * (exp(-(pow(((breath_counter / smoothness_pts) - beta) / theta, 2.0)) / 2.0));
      breath_counter++;
    } else {
      breath_counter = 0;
    }
    
    FastLED.setBrightness(breath_intensity);
    
    for (int i = 1; i < NUM_LEDS; i++) {
      leds[i] = CRGB::SandyBrown;
    }

    FastLED.show();
    last_update = millis();
  }
}


/**
 * @brief Function to turn off the LEDs and reset all the variables to the initial value
 *
 */
void LEDStrip::reset()
{
  FastLED.setBrightness(BRIGHTNESS);
  for (int i = 0; i < NUM_LEDS; i++) {
    leds[i] = CRGB::Black;
  }
  breath_counter = 0;
  FastLED.show();
}

