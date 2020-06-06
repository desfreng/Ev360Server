#include <iostream>

#include "Robot.h"

#include <csignal>

using namespace std;
using namespace ev3dev;

//bool break_while = false;

void my_handler(int s) {
    cout << "Catch signal : " << to_string(s) << endl;
//    break_while = true;
}

int main() {
    cout << "Debut" << endl;
    signal(SIGINT, my_handler);

    Robot r = Robot();

    r.set_position(45);

    r.set_power(100);

    this_thread::sleep_for(chrono::seconds (10));

    r.set_power(0);
    r.set_position(0);
    return 0;
}
