cmake_minimum_required(VERSION 3.7)
project(Ev360Server)

set(CMAKE_CXX_STANDARD 11)

add_executable(Ev360Server main.cpp ev3dev.h ev3dev.cpp RotatingWheel.cpp RotatingWheel.h Robot.cpp Robot.h BluetoothSocket.cpp BluetoothSocket.h BluetoothServer.cpp BluetoothServer.h Parser.cpp Parser.h)
target_link_libraries(Ev360Server libbluetooth.a)
