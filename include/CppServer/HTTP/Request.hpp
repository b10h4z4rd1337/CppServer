//
//  Request.hpp
//  Cpp_Server
//
//  Created by Mathias Tahas on 21.04.17.
//  Copyright © 2017 Mathias Tahas. All rights reserved.
//

#ifndef Request_hpp
#define Request_hpp

#include <map>
#include <string>
#include "Networking/Socket.hpp"

using namespace std;

namespace CppServer {
    class HTTPServer;
    
    class Request {
        
        friend class HTTPServer;
        
    private:
        Request(Socket *socket);
        void parse(Socket *socket);
        void parseHeader(const string& header);
        void parseParameters(const string& firstLine);
        
        string requestHeader, path, method;
        
    public:
        string& getPath();
        string& getMethod();
        map<string, string> headerMap;
        map<string, string> parameters;
        
        static bool headerEnded(string &head);
    };
}

#endif /* Request_hpp */
