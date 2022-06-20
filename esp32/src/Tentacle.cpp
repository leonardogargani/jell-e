#include "../Include/Actuators/Tentacle.h"


/**
 * @brief Construct a new Tentacle:: Tentacle object
 *
 */
Tentacle::Tentacle() : velocity(10), start_time(0), servos_in_use(false) {}


/**
 * @brief Initial setup of the tentacle: set servo motor pins and the easing function
 *
 */
void Tentacle::setup()
{
  servo_hor_ptr = &servo_hor;
  servo_vert_ptr = &servo_vert;
  servo_hor_ptr->setEasingType(EASE_CUBIC_IN_OUT);
  servo_vert_ptr->setEasingType(EASE_CUBIC_IN_OUT);
  servo_hor_ptr->attach(SERVO_2_PIN, 90);
  servo_vert_ptr->attach(SERVO_1_PIN, 90);
}


/**
 * @brief Function for the hello gesture: one servo motor moves up the tentacle, then the other motor moves the tentacle side to side
 *
 */
void Tentacle::sayHi()
{
  servo_vert_ptr->easeTo(50, velocity);
  for (int i = 0; i < 3; i++)
  {
    servo_hor_ptr->easeTo(50, 3.5 * velocity);
    servo_hor_ptr->easeTo(130, 3.5 * velocity);
  }
}

/**
 * @brief Function for the scared gesture: one motor moves up the tentacle, then the other servo motor moves the tentacle to the right
 *
 */
void Tentacle::scared()
{
  servo_hor_ptr->easeTo(50, 5 * velocity);
  servo_vert_ptr->easeTo(130, 5 * velocity);
  
}


/**
 * @brief Function for the angry gesture: one motor moves up the tentacle, then the other motor moves the tentacle side to side quickly
 *
 */
void Tentacle::angry()
{
  servo_vert_ptr->easeTo(50, velocity);
  for (int i = 0; i < 3; i++) {
    servo_hor_ptr->easeTo(70, 4.5 * velocity);
    servo_hor_ptr->easeTo(110, 4.5 * velocity);
  }
}

/**
 * @brief Function for the sad gesture: one servo motor moves down the tentacle
 *
 */
void Tentacle::sad()
{
  servo_vert_ptr->easeTo(130, velocity);
}


/**
 * @brief Function for the happy gesture: the tentacle does a V shape movement. one servo motor moves up the tentacle, then the other servo motor moves the tentacle side to side
 *
 */
void Tentacle::happy()
{
  bool previous_left = false;
  bool up = false;
  int counter = 0;
  while (counter <= 4) {
    // The tentacle moves up and right simultaneously
    if (!servos_in_use && !previous_left && !up) {
      start_time = millis();
      servo_hor_ptr->startEaseTo(50, 3.5 * velocity);
      servo_vert_ptr->startEaseTo(50, 3.5 * velocity);
      servos_in_use = true;
      previous_left = true;
      up = true;
    }

    // The tentacle is up, so it has to move back to the rest position
    if (!servos_in_use && up) {
      start_time = millis();
      servo_hor_ptr->startEaseTo(90, 3.5 * velocity);
      servo_vert_ptr->startEaseTo(90, 3.5 * velocity);
      servos_in_use = true;
      up = false;
    }

    // The tentacle moves up and left simultaneously
    if (!servos_in_use && previous_left && !up) {
      start_time = millis();
      servo_hor_ptr->startEaseTo(130, 3.5 * velocity);
      servo_vert_ptr->startEaseTo(50, 3.5 * velocity);
      servos_in_use = true;
      previous_left = false;
      up = true;
    }

    // Time to let the tentacle to move up or down
    if (millis() - start_time > 1000)
    {
      servos_in_use = false;
      if (!up)
        counter++;
    }
  }
}


/**
 * @brief Function to move back the tentacle to the rest position
 *
 */
void Tentacle::reset()
{
  servo_hor_ptr->easeTo(90, velocity);
  servo_vert_ptr->easeTo(90, velocity);
}

