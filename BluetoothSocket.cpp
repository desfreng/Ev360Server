//
// Created by gabriel on 13/06/2020.
//

#include "BluetoothSocket.h"

BluetoothSocket::BluetoothSocket(int fd, struct sockaddr_rc address) {
    _fd = fd;
    memset(_buf, 0, sizeof(_buf));

    _chan = address.rc_channel;
    ba2str(&address.rc_bdaddr, _buf);
    _addr = std::string(_buf);

    memset(_buf, 0, sizeof(_buf));
}

void BluetoothSocket::write(const std::string &data) const {
    ::write(_fd, data.c_str(), data.size());
}

std::string BluetoothSocket::read() {
    memset(_buf, 0, sizeof(_buf));
    ::read(_fd, _buf, sizeof(_buf));

    return std::string(_buf);
}

void BluetoothSocket::close() {
    memset(_buf, 0, sizeof(_buf));
    ::close(_fd);
}

int BluetoothSocket::getChannel() const {
    return _chan;
}

std::string BluetoothSocket::getAddress() const {
    return _addr;
}

BluetoothSocket::BluetoothSocket() {
    _fd = 0;
    _chan = 0;
}
