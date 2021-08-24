#include "robot.h"

Robot::Robot() {
    return;
}

Robot::~Robot() {
    return;
}

void Robot::Setup() {
    // Configure motor control pins
    PinMode(kMotorSpeedRight, OUTPUT);
    PinMode(kMotorSpeedLeft, OUTPUT);
    PinMode(kRightMotorDir1, OUTPUT);
    PinMode(kRightMotorDir2, OUTPUT);
    PinMode(kLeftMotorDir1, OUTPUT);
    PinMode(kLeftMotorDir2, OUTPUT);

    // Configure ultrasonic sensor pins
    pinMode(kUltrasonicEchoPin, OUTPUT); 
    pinMode(kUltrasonicTriggerPin, INPUT);
    digitalWrite(kUltrasonicTriggerPin, LOW);

    // Configure the IR line sensor pins
    PinMode(kIrSensor0, INPUT);
    PinMode(kIrSensor1, INPUT);
    PinMode(kIrSensor2, INPUT);
    PinMode(kIrSensor3, INPUT);
    PinMode(kIrSensor4, INPUT);

    // Configure the servo for the ultrasonic sensor
    ultrasonic_servo_.attach(kServoPin);
    ultrasonic_servo_.write(90);
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
}

int Robot::ReadUltrasonic() {
    // Reset the ultrasonic sensor
    digitalWrite(kUltrasonicTriggerPin, LOW);
    delayMicroseconds(2);
    
    // Emit a 10us pulse from the sensor
    digitalWrite(kUltrasonicTriggerPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(kUltrasonicTriggerPin, LOW);

    // Read in time it took for the sound wave to return to the sensor
    int duration = pulseIn(kUltrasonicEchoPin, HIGH);

    // Convert the time to a distance using the speed of sound
    int distance = duration * kUltrasonicDistanceConversion;
    return round(distance);
}

void Robot::SweepUltrasonic() {
    // Sets the requested positon of the servo, waits for it to
    // reach that position and then reads the ultrasonic sensor
    ultrasonic_servo_.write(180);
    delay(kServoDelayTimeMs*2); // double delay length to move from 0 to 180
    ultrasonic_distance_values_[0] = ReadUltrasonic();

    ultrasonic_servo_.write(135);
    delay(kServoDelayTimeMs);
    ultrasonic_distance_values_[1] = ReadUltrasonic();

    ultrasonic_servo_.write(90);
    delay(kServoDelayTimeMs);
    ultrasonic_distance_values_[2] = ReadUltrasonic();

    ultrasonic_servo_.write(45);
    delay(kServoDelayTimeMs);
    ultrasonic_distance_values_[3] = ReadUltrasonic();

    ultrasonic_servo_.write(0);
    delay(kServoDelayTimeMs);
    ultrasonic_distance_values_[4] = ReadUltrasonic();
}

void Robot::UpdateLineSensorValues() {
    ir_sensor_values_[0] = !digitalRead(kIrSensor0);
    ir_sensor_values_[1] = !digitalRead(kIrSensor1);
    ir_sensor_values_[2] = !digitalRead(kIrSensor2);
    ir_sensor_values_[3] = !digitalRead(kIrSensor3);
    ir_sensor_values_[4] = !digitalRead(kIrSensor4);
}

bool * Robot::GetIrSensorValues() {
    return ir_sensor_values_;
}
