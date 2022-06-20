#include "Arduino.h"
#include "ServoEasing.hpp"
#include "Include/Devices.h"

#define ACTION_TIME 5000
#define WAITING_TIME 2000


// Objects that defines our sensors and actuators
Button button; 
Microphone mic_sensor;
UltrasonicSensor distance_sensor;
LEDStrip led_strip;
Tentacle tentacle;

unsigned long last_timestamp = 0;
unsigned long start_action_millis = 0;
unsigned long end_action_millis = 0;
int squeezes = 0;

// Flag used to disable sensors while a gesture is working
bool disable = false;

// Flags used to say which emotion is in use
bool hello_in_use = false;
bool stay_away_in_use = false;
bool curious_in_use = false;
bool scared_in_use = false;
bool can_breathe = true;


void setup()
{
  button.setup();
  mic_sensor.setup();
  distance_sensor.setup();
  led_strip.setup();
  tentacle.setup();
  delay(3000);
}


/**
 * @brief Function that detects and reacts to button pressure.
 * 
 */ 
void detectionPressure()
{
  if (!disable) {
    int button_state = button.readPress();
    if (button_state == 0 && (millis() - button.getLastDebounce()) > DEBOUNCE) {
      disable = true;
      can_breathe = false;
      last_timestamp = millis();
      button.setLastDebounce(last_timestamp);
      button.updatePressCounter(); // 1

      // Check if we have a second touch in 2 seconds
      while (millis() - last_timestamp < WAITING_TIME) {
        if (millis() - button.getLastDebounce() > DEBOUNCE) {
          button_state = button.readPress();
          if (button_state == 0) {
            // Touched twice
            start_action_millis = millis();
            button.setLastDebounce(millis());
            button.updatePressCounter(); // 2
            break;
          }
        }
      }

      // Check if we have a long press
      last_timestamp = millis();
      while (millis() - last_timestamp < WAITING_TIME / 4) {
        if (millis() - button.getLastDebounce() > DEBOUNCE) {
          button_state = button.readPress();
          if (button_state == 0) {
            // Long press
            start_action_millis = millis();
            button.setLastDebounce(millis());
            button.updatePressCounter(); // 3
            break;
          }
        }
      }
    }
  }

  squeezes = button.getPressCounter();
  switch (squeezes)
  {
  case 1:
    // Happy Gesture (one press)
    led_strip.sad();
    tentacle.sad();
    break;
  case 2:
    // Sad Gesture (two presses)
    led_strip.happy();
    tentacle.happy();
    break;
  case 3:
    // Angry Gesture (long press)
    led_strip.angry();
    tentacle.angry();
    break;
  }

  // Reset everything after the action is ended
  if (squeezes > 0) {
    if (millis() - start_action_millis > ACTION_TIME) {
      button.resetPressCounter();
      disable = false;
      can_breathe = true;
      tentacle.reset();
      led_strip.reset();
      end_action_millis = millis();
    }
  }
}


/**
 * @brief Function that detects and reacts to microphone readings.
 * 
 */
void detectSound()
{
  if (!disable) {
    int mic_read = mic_sensor.readMic();
    if (abs(mic_read - mic_sensor.computeAverage()) >= LOUD) {
      // Scared Gesture
      scared_in_use = true;
      disable = true;
      can_breathe = false;
      start_action_millis = millis();
      led_strip.scared();
      tentacle.scared();
    }
  }

  if (scared_in_use) {
    if (millis() - start_action_millis > ACTION_TIME) {
      scared_in_use = false;
      disable = false;
      can_breathe = true;
      tentacle.reset();
      led_strip.reset();
      end_action_millis = millis();
    }
  }
}


/**
 * @brief Function that detect and react to Ultrasonic sensor readings.
 * 
 */
void detectDistance()
{
  if (!disable) {
    int distance_read = distance_sensor.readDistance();
    distance_sensor.updateSwingCounter(distance_read);
    // Say Hello
    if (distance_sensor.getSwingCounter() >= MIN_SWING) {
      // Actions for saying hello
      hello_in_use = true;
      disable = true;
      can_breathe = false;
      start_action_millis = millis();
      distance_sensor.resetSwingCounter();
    }
    // Too near
    if (distance_read < MIN_DISTANCE) {
      // Stay away actions
      distance_sensor.resetSwingCounter();
      led_strip.angry();
      stay_away_in_use = true;
      disable = true;
      can_breathe = false;
      start_action_millis = millis();
    }
}

  if (hello_in_use) {
    led_strip.hello();
    tentacle.sayHi();
  } else if (stay_away_in_use) {
    tentacle.angry();
}

if (hello_in_use || stay_away_in_use) {
    if (millis() - start_action_millis > ACTION_TIME) {
        hello_in_use = false;
        stay_away_in_use = false;
        disable = false;
        can_breathe = true;
        distance_sensor.resetSwingCounter();
        tentacle.reset();
        led_strip.reset();
        end_action_millis = millis();
    }
  }
}

int swing_counter = 0;
int previous_distance = 0;


void loop()
{
  /************TOUCH CONTROL************/
  detectionPressure();

  /************SOUND CONTROL************/
  detectSound();

  /************DISTANCE CONTROL*********/
  detectDistance();

  /************BREATH CONTROL***********/
  if (can_breathe) {
    led_strip.breath();
  }

}

