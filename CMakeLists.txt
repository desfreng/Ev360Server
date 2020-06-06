cmake_minimum_required(VERSION 3.7)
project(Ev360Mover)

set(CMAKE_CXX_STANDARD 11)

add_executable(Ev360Mover main.cpp ev3dev.h ev3dev.cpp RotatingWheel.cpp RotatingWheel.h Robot.cpp Robot.h)
