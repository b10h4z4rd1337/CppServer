//
//  ServerSocket.cpp
//  Cpp_Server
//
//  Created by Mathias Tahas on 21.04.17.
//  Copyright © 2017 Mathias Tahas. All rights reserved.
//

#include "C_Socket_Helper.h"
#include "ServerSocket.hpp"

using namespace CppServer;

ServerSocket::ServerSocket(int port) {
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = PF_INET;
    server_addr.sin_port = htons(port);
    server_addr.sin_addr.s_addr = INADDR_ANY;
    
    fd = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
    
    if(!fd) {
        perror("server");
    }
    
    int reuse = 1;
    if (setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(reuse)) < 0){
        perror("sockopt");
    }
    
    if (bind(fd,(const struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("bind");
    }
}

ServerSocket::~ServerSocket() {
    if (!closed) {
        close();
    }
}

bool ServerSocket::listen() {
    if (C_listen(fd, SOMAXCONN) < 0) {
        perror("listen");
        return false;
    }
    closed = false;
    return true;
}

Socket* ServerSocket::accept() {
    struct sockaddr_in client_addr;
    int client_fd = C_accept(fd, (struct sockaddr*)&client_addr);
    Socket *socket = new Socket(client_fd);
    return socket;
}

void ServerSocket::close() {
    C_close(fd);
    closed = true;
}
