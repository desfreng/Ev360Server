//
// Created by gabriel on 13/06/2020.
//

#include "BluetoothServer.h"
#include "BluetoothSocket.h"

BluetoothServer::BluetoothServer() {
    _fd = socket(AF_BLUETOOTH, SOCK_STREAM, BTPROTO_RFCOMM);
}

void BluetoothServer::bind(int channel) const {
    struct sockaddr_rc loc_addr = {};

    loc_addr.rc_family = AF_BLUETOOTH;
    loc_addr.rc_bdaddr = (bdaddr_t) {{0, 0, 0, 0, 0, 0}};
    loc_addr.rc_channel = (uint8_t) channel;
    ::bind(_fd, reinterpret_cast<sockaddr *>(&loc_addr), sizeof(loc_addr));

}

BluetoothSocket BluetoothServer::accept() const {
    struct sockaddr_rc rem_addr{};
    socklen_t opt = sizeof(rem_addr);

    int client = ::accept(_fd, reinterpret_cast<sockaddr *>(&rem_addr), &opt);

    return BluetoothSocket(client, rem_addr);
}

void BluetoothServer::listen() const {
    ::listen(_fd, 1);
}

void BluetoothServer::close() const {
    ::close(_fd);
}

int BluetoothServer::getChannel() const {
    struct sockaddr_rc sin{};
    socklen_t len = sizeof(sin);

    if (getsockname(_fd, reinterpret_cast<sockaddr *>(&sin), &len) == -1)
        throw std::runtime_error("Unable to get channel");
    else
        return sin.rc_channel;
}

/*
    struct sockaddr_rc loc_addr = {0}, rem_addr = {0};
    char buf[1024];
    int bytes_read;
    socklen_t opt = sizeof(rem_addr);

    // allocate socket
    s = socket(AF_BLUETOOTH, SOCK_STREAM, BTPROTO_RFCOMM);

    // bind socket
    loc_addr.rc_family = AF_BLUETOOTH;
    loc_addr.rc_bdaddr = addr_any;
    loc_addr.rc_channel = (uint8_t) 0;
    bind(s, reinterpret_cast<sockaddr *>(&loc_addr), sizeof(loc_addr));

    // put socket into listening mode
    listen(s, 1);

    struct sockaddr_rc sin{};
    socklen_t len = sizeof(sin);
    if (getsockname(s, reinterpret_cast<sockaddr *>(&sin), &len) == -1)
        perror("getsockname");
    else
        printf("port number %d\n", sin.rc_channel);

    cout << "All Ok !" << endl;
    client = accept(s, reinterpret_cast<sockaddr *>(&rem_addr), &opt);

    ba2str(&rem_addr.rc_bdaddr, buf);
    fprintf(stderr, "accepted connection from %s\n", buf);
    memset(buf, 0, sizeof(buf));
*/
