//
//  C_Socket_Helper.c
//  Cpp_Server
//
//  Created by Mathias Tahas on 21.04.17.
//  Copyright © 2017 Mathias Tahas. All rights reserved.
//

#include "C_Socket_Helper.h"

socklen_t sock_len = sizeof(struct sockaddr_in);

ssize_t CppServer::C_read(int fd, void* data, size_t len) {
    return read(fd, data, len);
}

ssize_t CppServer::C_write(int fd, const void* data, size_t len) {
    return write(fd, data, len);
}

int CppServer::C_close(int fd) {
    return close(fd);
}

int CppServer::C_listen(int fd, int count) {
    return listen(fd, count);
}

int CppServer::C_accept(int fd, struct sockaddr * sock_addr) {
    return accept(fd, sock_addr, &sock_len);
}
