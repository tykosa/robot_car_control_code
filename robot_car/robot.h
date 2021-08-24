/**
 * Author: Tyler Kosakowski
 * Date: 8/22/2021
 * 
 * 
 * Style Guide: https://google.github.io/styleguide/cppguide.html
 * 
 * This header file contains the class declaration for interfacing with
 * the Osoyoo Robot Car v2.1
 * 
 */



#ifndef ROBOT_CORE_H
#define ROBOT_CORE_H

#include "Arduino.h"

enum DriveDirection {
  kForward = 0,
  kBackward = 1,
  kLeft = 2,
  kRight = 3,
  kStop = 4
};

class Robot {
    private:
        // Boolean Array holding the data read from the line sensors
        bool ir_sensor_values_[5];

        // ir_sensor_0 - 4 are the 5 ir line following sensors
        // these are each assigned a pin number here
        const int kIrSensor0 = A0;
        const int kIrSensor1 = A1;
        const int kIrSensor2 = A2;
        const int kIrSensor3 = A3;
        const int kIrSensor4 = A4;

        // Speed control pins for each side of the robot
        const int kMotorSpeedRight = 3;
        const int kMotorSpeedLeft = 6;
        
        // Direction control pins for each of the motors
        const int kRightMotorDir1 = 11;
        const int kRightMotorDir2 = 12;
        const int kLeftMotorDir1 = 8;
        const int kLeftMotorDir2 = 7;

        // Ultrasonic control pins
        const int kUltrasonicEchoPin = 2;
        const int kUltrasonicTriggerPin = 10;

        // Servo control pins
        const int kServoPin = 9;

        // Default motor speed
        const int kDefaultMotorSpeed = 200;

        // Ultrasonic distance conversion constant (result is in cm)
        const double kUltrasonicDistanceConversion = 0.017;

        // Ultrasonic detection distance limit (units in cm)
        const int kUltrasonicDistanceLimit = 40;

    public:
        // Constructor
        Robot();

        // Destructor
        ~Robot();

        // Setup Method to initalize all of the pin configurations
        void Setup();

        // Robot driving control method
        // @param dir direction to drive in
        // @param duration how long to spend before returning from drive
        // @param left_motor_speed how fast to run the left motors
        // @param right_motor_speed how fast to run the right motors
        void Drive(
        DriveDirection dir,
        int duration=0,
        int left_motor_speed=kDefaultMotorSpeed,
        int right_motor_speed=kDefaultMotorSpeed);
        
        // Reads the ultrasonic sensor and returns the distance to an obstacle
        int ReadUltrasonic();

        // Reads each of the ir line sensors and stores the values
        void UpdateLineSensorValues();

        // getter for the ir line sensors array
        bool * GetIrSensorValues();
};



#endif // ROBOT_CODE_H
