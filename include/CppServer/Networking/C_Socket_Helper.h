//
//  C_Socket_Helper.h
//  Cpp_Server
//
//  Created by Mathias Tahas on 21.04.17.
//  Copyright © 2017 Mathias Tahas. All rights reserved.
//

#ifndef C_Socket_Helper_h
#define C_Socket_Helper_h

#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>

#include <string>

namespace CppServer {
    ssize_t C_read(int fd, void* data, size_t len);
    ssize_t C_write(int fd, const void* data, size_t len);
    int C_close(int fd);
    int C_listen(int fd, int count);
    int C_accept(int fd, struct sockaddr * sock_addr);
}

#endif /* C_Socket_Helper_h */
