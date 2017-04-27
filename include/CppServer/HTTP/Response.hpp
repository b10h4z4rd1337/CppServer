//
//  Response.hpp
//  Cpp_Server
//
//  Created by Mathias Tahas on 21.04.17.
//  Copyright © 2017 Mathias Tahas. All rights reserved.
//

#ifndef Response_hpp
#define Response_hpp

#include "Networking/Socket.hpp"
#include <string>
#include <map>

using namespace std;

namespace CppServer {
    class HTTPServer;
    
    class ResponseException : public exception {
    private:
        string message;
        
    public:
        ResponseException(string message) : message(message){ }
        virtual string what() throw() {
            return message;
        }
    };
    
    class Response {
        
        friend class HTTPServer;
        
    private:
        Socket *socket = NULL;
        map<string, string> headerMap;
        Response(Socket* socket);
        bool header = false;
        
        inline void checkForHeader();
        inline void checkHeaderErrors();
        
    public:
        ~Response();
        void write(const void* data, size_t size);
        void write(const string& data);
        void setHeader(string key, string value);
    };
}

#endif /* Response_hpp */
