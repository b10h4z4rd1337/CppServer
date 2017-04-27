//
//  HTTPServer.hpp
//  Cpp_Server
//
//  Created by Mathias Tahas on 21.04.17.
//  Copyright © 2017 Mathias Tahas. All rights reserved.
//

#ifndef HTTPServer_hpp
#define HTTPServer_hpp

#include "Networking/ServerSocket.hpp"
#include "HTTP/Request.hpp"
#include "HTTP/Response.hpp"
#include "HTTP/FileHandler.hpp"
#include "HTTP/HTMLDocument.hpp"
#include "ThreadPool.hpp"

#include <map>
#include <thread>
#include <functional>

using namespace std;

namespace CppServer {
    
    typedef function<void(Request&, Response&)> lambda;
    
    class HTTPServer {
    public:
        HTTPServer(int port);
        ~HTTPServer();
        void start();
        void addRoute(const string& method, const string& path, const lambda& lam);
        void addRoute(const string& method, const string& path, const HTMLDocument& doc);
        void addRoute(const FileHandler& fileHandler);
        
        void removeRoute(const string& method, const string& path);
        void removeRoute(const string& method, const HTMLDocument& doc);
        void removeRoute(const FileHandler& fileHandler);
        
        inline void removeHelper(const string& path, map<const string, lambda> &map);
        
    private:
        map<const string, lambda> getRoutes;
        map<const string, lambda> postRoutes;
        ServerSocket *serverSocket;
        ThreadPool *threadPool;
        
        static void threadRoutine(HTTPServer *httpServer, Socket* socket);
        static void handleNotFound(Request& req, Response& resp);
    };
}

#endif /* HTTPServer_hpp */
