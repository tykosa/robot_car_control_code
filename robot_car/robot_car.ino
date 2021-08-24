/*
 * Author: Tyler Kosakowski
 * 
 * This program is an object oriented interface layer for working with the Osoyoo robot car
 * 
 * 
 * 
 */

#include "robot.h"

Robot robot;


void setup() {
  robot.Setup();
  robot.drive(DRIVE_DIRECTION::FORWARD);
}

void loop() {

}
