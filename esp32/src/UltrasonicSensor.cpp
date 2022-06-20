#include "Arduino.h"
#include "../Include/Sensors/UltrasonicSensor.h"


/** 
 * @brief Construct a new Ultrasonic::Ultrasonic object 
 * 
 */
UltrasonicSensor::UltrasonicSensor() : duration(0), swing_counter(0), previous_distance(0), last_update(0)
{
}


/**
 * @brief Setup ultrasonic sensor pins. Echo pin as input and trigger pin as output.
 * 
 */
void UltrasonicSensor::setup()
{
  pinMode(TRIGGER_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  previous_distance = this->readDistance();
}


/**
 * @brief Read the distance detected from the ultrasonic sensor.
 * The function send a signal through the trigger pin and then read the time of flight from 
 * the echo pin. The distance is calculated with the following formula:
 * duration*sound_speed / 2.
 * @return Distance read in centimeter.
 * 
 */ 
int UltrasonicSensor::readDistance()
{
  int distance;
  digitalWrite(TRIGGER_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIGGER_PIN, HIGH);
  delayMicroseconds(100);
  digitalWrite(TRIGGER_PIN, LOW);
  duration = pulseIn(ECHO_PIN, HIGH);
  distance = duration * 0.034 / 2;
  if (distance >= 1000 || distance == 0) {
    distance = previous_distance;
  }
  return distance;
}


/**
 * @brief Get the number of current swings detected.
 * @return the number of current swings detected.
 * 
 */
int UltrasonicSensor::getSwingCounter()
{
  return swing_counter;
}


/**
 * @brief Reset the number of swing detected.
 * 
 */ 
void UltrasonicSensor::resetSwingCounter()
{
  swing_counter = 0;
}

/**
 * @brief Update the current number of swing detected.
 * This function is used to trigger the sayHello gesture.
 * A swing is detected if in less than 1.5 meters there is a variation of measurment of 20 centimeters.
 * 
 */ 
void UltrasonicSensor::updateSwingCounter(int distance)
{

  if (millis() - last_update > 500 && ((distance - previous_distance) > DELTA_DISTANCE) && distance < 150) {
    last_update = millis();
    swing_counter++; 
  } if (distance > MAX_DISTANCE) //if someone goes away reset the swing_counter
    swing_counter = 0;
  previous_distance = distance;
}
