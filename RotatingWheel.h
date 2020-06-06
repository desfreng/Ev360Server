//
// Created by gabriel on 26/04/2020.
//

#ifndef EV360MOVER_ROTATING_WHEEL_H
#define EV360MOVER_ROTATING_WHEEL_H

#include "ev3dev.h"
#include <exception>
#include <thread>
#include <iostream>

class RotatingWheel {
public:

    enum location {
        LEFT,
        RIGHT,
        UP
    };

    explicit RotatingWheel(const ev3dev::address_type &addr, int degrees, location location, int power);

    void set_position(int position, bool block = false);

    void move(int position);

    int get_position() const;

    void rotating_position(bool inverse = false);

    bool is_running() const;

private:
    int rel2abs(int rel) const;

    int abs2rel(int abs) const;

    void _debug(const char msg[]) const;

    ev3dev::large_motor _motor;
    double _coef;
    int _begin_deg;
    bool _debug_on = true;

    location _loc;
};


#endif //EV360MOVER_ROTATING_WHEEL_H
