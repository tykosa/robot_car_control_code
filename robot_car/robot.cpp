#include "robot.h"

Robot::Robot() {
    return;
}

Robot::~Robot() {
    return;
}

void Robot::Setup() {
    return;
}

void Robot::Drive(
        DriveDirection dir,
        int duration,
        int left_motor_speed,
        int right_motor_speed) {
    switch (dir) {
        case kForward:
            digitalWrite(kRightMotorDir1, HIGH);
            digitalWrite(kRightMotorDir2, LOW);
            digitalWrite(kLeftMotorDir1, HIGH);
            digitalWrite(kLeftMotorDir2, LOW);
            analogWrite(kMotorSpeedLeft, left_motor_speed);
            analogWrite(kMotorSpeedRight, right_motor_speed);
            delay(duration);
            break;
        case kBackward:
            digitalWrite(kRightMotorDir1, LOW);
            digitalWrite(kRightMotorDir2, HIGH);
            digitalWrite(kLeftMotorDir1, LOW);
            digitalWrite(kLeftMotorDir2, HIGH);
            analogWrite(kMotorSpeedLeft, left_motor_speed);
            analogWrite(kMotorSpeedRight, right_motor_speed);
            delay(duration);
            break;
        case kLeft:
            digitalWrite(kRightMotorDir1, LOW);
            digitalWrite(kRightMotorDir2, HIGH);
            digitalWrite(kLeftMotorDir1, HIGH);
            digitalWrite(kLeftMotorDir2, LOW);
            analogWrite(kMotorSpeedLeft, left_motor_speed);
            analogWrite(kMotorSpeedRight, right_motor_speed);
            delay(duration);
            break;
        case kRight:
            digitalWrite(kRightMotorDir1, HIGH);
            digitalWrite(kRightMotorDir2, LOW);
            digitalWrite(kLeftMotorDir1, LOW);
            digitalWrite(kLeftMotorDir2, HIGH);
            analogWrite(kMotorSpeedLeft, left_motor_speed);
            analogWrite(kMotorSpeedRight, right_motor_speed);
            delay(duration);
            break;
        case kStop:
            digitalWrite(kRightMotorDir1, LOW);
            digitalWrite(kRightMotorDir2, LOW);
            digitalWrite(kLeftMotorDir1, LOW);
            digitalWrite(kLeftMotorDir2, LOW);
            analogWrite(kMotorSpeedLeft, 0);
            analogWrite(kMotorSpeedRight, 0);
            break;
        default:
            digitalWrite(kRightMotorDir1, LOW);
            digitalWrite(kRightMotorDir2, LOW);
            digitalWrite(kLeftMotorDir1, LOW);
            digitalWrite(kLeftMotorDir2, LOW);
            delay(duration);
            break;
    }
    return;
}

int Robot::ReadUltrasonic() {
    
    return;
}

void Robot::UpdateLineSensorValues() {

    return;
}

bool * Robot::GetIrSensorValues() {
    return ir_sensor_values_;
}