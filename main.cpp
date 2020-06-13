#include <iostream>
#include <csignal>
#include "BluetoothServer.h"

#include "Robot.h"
#include "BluetoothSocket.h"
#include "Parser.h"

using namespace std;
using namespace ev3dev;

BluetoothServer server;
BluetoothSocket client;

void my_handler(int s) {
    cout << "Catch signal : " << to_string(s) << endl;
    client.write("ST#");
}

int main() {
    cout << "Debut" << endl;
    signal(SIGINT, my_handler);
    signal(SIGTERM, my_handler);

    Robot r = Robot();

    server.bind();
    server.listen();

    cout << "Channel : " << server.getChannel() << endl;

    client = server.accept();

    cout << "Accepted Connection from : " << client.getAddress() << "@" << client.getChannel()
         << endl;

    bool reading = true;
    Parser p("#");

    while (reading) {
        string data = client.read();
        if (!data.empty()) {
            p.addData(data);
            while (!p.isEmpty()) {
                Parser::Action a = p.lastAction();
                cout << a.toString() << endl;
                switch (a.action) {
                    case Parser::TurnLeft:
                        r.rotate(true);
                        break;
                    case Parser::TurnRight:
                        r.rotate();
                        break;
                    case Parser::ResetWheels:
                        r.set_position(0);
                        break;
                    case Parser::Direction:
                        r.set_position(a.data);
                        break;
                    case Parser::Power:
                        r.set_power(a.data);
                        break;
                    case Parser::Stop:
                        cout << "Stop..." << endl;
                        reading = false;
                        break;
                    case Parser::None:
                        break;
                }
            }
        }
    }

    client.close();
    server.close();

    return 0;
}
