//
//  Socket.h
//  Cpp_Server
//
//  Created by Mathias Tahas on 21.04.17.
//  Copyright © 2017 Mathias Tahas. All rights reserved.
//

#ifndef Socket_h
#define Socket_h

#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>

#define BUFFER_SIZE 1024

namespace CppServer {
    class ServerSocket;
    class Socket {
        friend class ServerSocket;
        
    private:
        Socket(int fd);
        int fd = 0;
        struct sockaddr_in client_addr;
        bool closed = true;
        
    public:
        ~Socket();
        ssize_t read(void* buffer, size_t len);
        ssize_t write(const void* buffer, size_t len);
        void close();
    };
}



#endif /* Socket_h */
