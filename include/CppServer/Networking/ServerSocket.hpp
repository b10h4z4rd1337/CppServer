//
//  ServerSocket.hpp
//  Cpp_Server
//
//  Created by Mathias Tahas on 21.04.17.
//  Copyright © 2017 Mathias Tahas. All rights reserved.
//

#ifndef ServerSocket_hpp
#define ServerSocket_hpp

#include "Socket.hpp"

namespace CppServer {
    class ServerSocket {
    private:
        int fd = 0;
        struct sockaddr_in server_addr;
        bool closed = true;
    
    public:
        ServerSocket(int port);
        ~ServerSocket();
        bool listen();
        Socket* accept();
        void close();
    };
}



#endif /* ServerSocket_hpp */
