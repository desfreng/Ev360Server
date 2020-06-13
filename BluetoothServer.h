//
// Created by gabriel on 13/06/2020.
//

#ifndef EV360MOVER_BLUETOOTH_SERVER_H
#define EV360MOVER_BLUETOOTH_SERVER_H

#include <unistd.h>
#include <sys/socket.h>
#include <bluetooth/bluetooth.h>
#include <bluetooth/rfcomm.h>
#include <stdexcept>

class BluetoothSocket;

class BluetoothServer {
public:
    BluetoothServer();

    void bind(int channel = 0) const;

    void listen() const;

    BluetoothSocket accept() const;

    void close() const;

    int getChannel() const;

private:
    int _fd;
};

#endif //EV360MOVER_BLUETOOTH_SERVER_H
