//
// Created by gabriel on 26/04/2020.
//

#include "Robot.h"

Robot::Robot() : _power(ev3dev::OUTPUT_A),
                 _up(ev3dev::OUTPUT_B, 2520, RotatingWheel::UP, 50),
                 _right(ev3dev::OUTPUT_C, 2520, RotatingWheel::RIGHT, 50),
                 _left(ev3dev::OUTPUT_D, -1800, RotatingWheel::LEFT, 36),
                 _gs(), _us(), _ts() {
    _power.set_stop_action(ev3dev::large_motor::stop_action_coast);
    _power.run_direct();

    stop();

    _gs.set_mode(ev3dev::gyro_sensor::mode_gyro_ang);
    _us.set_mode(ev3dev::ultrasonic_sensor::mode_us_dist_cm);
    _ts.set_mode(ev3dev::touch_sensor::mode_touch);

    gyro_cal();
}

Robot::~Robot() {
    _power.stop();
}

void Robot::set_position(int position) {
    _up.set_position(position, false);
    _right.set_position(position, false);
    _left.set_position(position, true);

    wait_running();
}

void Robot::set_power(int percent) {
    _power.set_duty_cycle_sp(percent);
}

const RotatingWheel &Robot::up_wheel() const {
    return _up;
}

const RotatingWheel &Robot::right_wheel() const {
    return _right;
}

const RotatingWheel &Robot::left_wheel() const {
    return _left;
}

void Robot::rotate(bool inverse) {
    _up.rotating_position(inverse);
    _right.rotating_position(inverse);
    _left.rotating_position(inverse);

    wait_running();
}

void Robot::stop() {
    _power.set_duty_cycle_sp(0);
}

void Robot::wait_running() const {
    while (_up.is_running() or _right.is_running() or _left.is_running())
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
}

void Robot::gyro_cal() {
    _gs.set_mode(ev3dev::gyro_sensor::mode_gyro_cal);
    std::this_thread::sleep_for(std::chrono::seconds(2));
    _gs.set_mode(ev3dev::gyro_sensor::mode_gyro_ang);
}

int Robot::angle() {
    return _gs.angle();
}

float Robot::distance() {
    return _us.distance_centimeters();
}

bool Robot::pressed() {
    return _ts.is_pressed();
}

