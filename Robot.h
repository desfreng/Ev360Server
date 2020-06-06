//
// Created by gabriel on 26/04/2020.
//

#ifndef EV360MOVER_ROBOT_H
#define EV360MOVER_ROBOT_H

#include "ev3dev.h"

#include "RotatingWheel.h"

class Robot {
public:
    Robot();

    ~Robot();

    void set_position(int position);

    void set_power(int percent);

    const RotatingWheel &up_wheel() const;

    const RotatingWheel &right_wheel() const;

    const RotatingWheel &left_wheel() const;

    void rotate(bool inverse = false);

    void stop();

    void gyro_cal();

    int angle();

    float distance();

    bool pressed();

private:

    void wait_running() const;

    ev3dev::large_motor _power;

    RotatingWheel _up;
    RotatingWheel _right;
    RotatingWheel _left;

    ev3dev::gyro_sensor _gs;
    ev3dev::touch_sensor _ts;
    ev3dev::ultrasonic_sensor _us;
};


#endif //EV360MOVER_ROBOT_H
