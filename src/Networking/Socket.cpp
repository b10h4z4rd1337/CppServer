//
//  Socket.cpp
//  Cpp_Server
//
//  Created by Mathias Tahas on 21.04.17.
//  Copyright © 2017 Mathias Tahas. All rights reserved.
//

#include "C_Socket_Helper.h"
#include "Socket.hpp"

using namespace CppServer;

Socket::Socket(int fd) {
    this->fd = fd;
    this->closed = false;
}

Socket::~Socket() {
    if (!closed) {
        C_close(fd);
    }
}

ssize_t Socket::read(void *buffer, size_t len) {
    return C_read(fd, buffer, len);
}

ssize_t Socket::write(const void *buffer, size_t len) {
    return C_write(fd, buffer, len);
}

void Socket::close() {
    C_close(fd);
    closed = true;
}
