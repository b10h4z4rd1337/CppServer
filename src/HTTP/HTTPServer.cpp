//
//  HTTPServer.cpp
//  Cpp_Server
//
//  Created by Mathias Tahas on 21.04.17.
//  Copyright © 2017 Mathias Tahas. All rights reserved.
//

#include "HTTPServer.hpp"
#include <sstream>
#include <typeinfo>

using namespace CppServer;

HTTPServer::HTTPServer(int port) {
    serverSocket = new ServerSocket(port);
    threadPool = new ThreadPool;
}

HTTPServer::~HTTPServer() {
    delete serverSocket;
    delete threadPool;
}

void HTTPServer::start() {
    this->serverSocket->listen();
    
    while (true) {
        Socket *socket = this->serverSocket->accept();
        threadPool->appendJob(bind(HTTPServer::threadRoutine, this, socket));
    }
}

void HTTPServer::threadRoutine(HTTPServer *httpServer, Socket* socket) {
    Request request(socket);
    Response response(socket);
    string method = request.getMethod();
    string path = request.getPath();
    
    lambda functor;
    
    if (method == "GET") {
        auto it = httpServer->getRoutes.find(path);
        if (it == httpServer->getRoutes.end()) {
            handleNotFound(request, response);
        } else {
            functor = (*it).second;
        }
    } else if (method == "POST") {
        auto it = httpServer->postRoutes.find(path);
        if (it == httpServer->postRoutes.end()) {
            handleNotFound(request, response);
        } else {
            lambda functor = (*it).second;
        }
    }
    
    functor(request, response);
}

void HTTPServer::addRoute(const FileHandler& fileHandler) {
    getRoutes.insert(pair<const string, lambda>(fileHandler.getPath(), fileHandler));
}

void HTTPServer::addRoute(const string& method, const string& path, const lambda& lam) {
    if (method == "GET") {
        getRoutes.insert(pair<const string, lambda>(path, lam));
    } else if (method == "POST") {
        postRoutes.insert(pair<const string, lambda>(path, lam));
    }
    
}

void HTTPServer::addRoute(const string& method, const string &path, const HTMLDocument& doc) {
    if (method == "GET") {
        getRoutes.insert(pair<const string, lambda>(path, doc));
    } else if (method == "POST") {
        postRoutes.insert(pair<const string, lambda>(path, doc));
    }
    
    for (auto handler : *(doc.fileHandles)) {
        addRoute(handler);
    }
}

inline void HTTPServer::removeHelper(const string& path, map<const string, lambda> &map) {
    lambda lam = map[path];
    if (typeid(lam) == typeid(HTMLDocument)) {
        for (auto it : *(reinterpret_cast<HTMLDocument*>(&lam)->fileHandles)) {
            removeRoute(it);
        }
    }
    map.erase(path);
}

void HTTPServer::removeRoute(const string& method, const string &path) {
    if (method == "GET") {
        removeHelper(path, getRoutes);
    } else if (method == "POST") {
        removeHelper(path, postRoutes);
    }
}

void HTTPServer::removeRoute(const FileHandler &fileHandler) {
    getRoutes.erase(fileHandler.getPath());
}

void HTTPServer::handleNotFound(Request &req, Response &resp) {
    resp.setHeader("Status", "404 Not Found");
    resp.setHeader("Content-Length", "13");
    resp.write("404 Not found");
}
