//
// Created by gabriel on 13/06/2020.
//

#ifndef EV360MOVER_BLUETOOTHSOCKET_H
#define EV360MOVER_BLUETOOTHSOCKET_H


#include <string>
#include <unistd.h>
#include <sys/socket.h>
#include <bluetooth/bluetooth.h>
#include <bluetooth/rfcomm.h>
#include "BluetoothServer.h"


class BluetoothSocket {
public:
        explicit BluetoothSocket();

    void write(const std::string &data) const;

    std::string read();

    void close();

    int getChannel() const;

    std::string getAddress() const;

private:
    friend BluetoothSocket BluetoothServer::accept() const;

    explicit BluetoothSocket(int fd, struct sockaddr_rc address);

    int _fd;
    char _buf[1024]{0};
    int _chan;
    std::string _addr;
};


#endif //EV360MOVER_BLUETOOTHSOCKET_H
