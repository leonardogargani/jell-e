#include "../Include/Sensors/Button.h"


/** 
 * @brief Construct a new Button::Button object 
 * 
 */
Button::Button() : press_counter(0), last_debounce_time(0)
{
}


/**
 * @brief Setup the button pin as input pullup.
 * 
 */
void Button::setup()
{
  pinMode(BUTTON_PIN, INPUT_PULLUP);
}


/**
 * @brief Read the digital signal received on the button pin.
 * @return - 1 if the button is NOT pressed.
 *         - 0 if the button is pressed.
 * 
 */
int Button::readPress()
{
  return digitalRead(BUTTON_PIN);
}


/**
 * @brief Get the last debounce time.
 * @return timestamp of the last debounce.
 * 
 */
long int Button::getLastDebounce()
{
  return last_debounce_time;
}


/**
 * @brief Set last debounce time.
 * 
 */ 
void Button::setLastDebounce(long int last_debounce)
{
  last_debounce_time = last_debounce;
}


/**
 * @brief Get the number of current pression
 * @return Number of current pression.
 * 
 */ 
int Button::getPressCounter()
{
  return press_counter;
}


/**
 * @brief Update the current number of pression.
 * 
 */
void Button::updatePressCounter()
{
  press_counter++;
}


/**
 * @brief Reset the squeeze counter.
 */
void Button::resetPressCounter()
{
  press_counter = 0;
}

