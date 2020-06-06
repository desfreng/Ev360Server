//
// Created by gabriel on 26/04/2020.
//

#include "RotatingWheel.h"


RotatingWheel::RotatingWheel(const ev3dev::address_type &addr, int degrees, location loc, int power)
        : _motor(addr), _loc(loc) {

    _coef = degrees / 360.0;

    _begin_deg = static_cast<int>(_motor.position() / _coef);
    _motor.set_stop_action(ev3dev::large_motor::stop_action_hold);
    _motor.set_speed_sp(power * _motor.max_speed() / 100);
}

void RotatingWheel::set_position(int position, bool block) {

    position = position;

    _motor.set_position_sp(rel2abs(position));
    _motor.run_to_abs_pos();

    if (block)
        while (_motor.state().count(ev3dev::large_motor::state_running))
            std::this_thread::sleep_for(std::chrono::milliseconds(10));

}

void RotatingWheel::move(int position) {
    set_position(get_position() + position);
}

int RotatingWheel::get_position() const {
    int value = abs2rel(_motor.position());

    return value % 360;
}

void RotatingWheel::rotating_position(bool inverse) {
    switch (_loc) {
        case UP:
            if (inverse)
                set_position(-90);
            else
                set_position(90);
            break;

        case RIGHT:
            if (inverse)
                set_position(30);
            else
                set_position(210);
            break;

        case LEFT:
            if (inverse)
                set_position(150);
            else
                set_position(-30);
            break;
    }
}

int RotatingWheel::rel2abs(int rel) const {
    return static_cast<int>((rel + _begin_deg) * _coef);
}

int RotatingWheel::abs2rel(int abs) const {
    return static_cast<int>(abs / _coef) - _begin_deg;
}

void RotatingWheel::_debug(const char msg[]) const {
    if (_debug_on) {
        std::cout << msg << std::endl;
    }
}

bool RotatingWheel::is_running() const {
    return _motor.state().count(ev3dev::large_motor::state_running);
}
