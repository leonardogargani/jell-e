#ifndef CAPACITIVE_H
#define CAPACITIVE_H

#include "Arduino.h"
#include "../Pins.h"

#define DEBOUNCE 300


/**
 * @brief Class that define the button.
 */
class Button
{
private:
  int press_counter;            // Press counter 
  long int last_debounce_time;  // Variable used to perform debouncing

public:
  Button();
  void setup();
  int readPress();
  long int getLastDebounce();
  void setLastDebounce(long int last_debounce);
  int getPressCounter();
  void updatePressCounter();
  void resetPressCounter();
};

#endif
