//
//  Response.cpp
//  Cpp_Server
//
//  Created by Mathias Tahas on 21.04.17.
//  Copyright © 2017 Mathias Tahas. All rights reserved.
//

#include "Response.hpp"
#include <sstream>

using namespace CppServer;

Response::Response(Socket* socket) {
    this->socket = socket;
    
    //Add default response headers
    headerMap["Status"] = "200 OK";
    headerMap["Content-Type"] = "text/html";
    headerMap["Content-Length"] = "-1";
    headerMap["Connection"] = "close";
}

Response::~Response() {
    delete socket;
}

inline void Response::checkHeaderErrors() {
    //Check Headers and throw Exception if necessary
    if (stol(headerMap["Content-Length"]) < 0) {
        throw ResponseException("No or wrong Content-Length");
    }
}

const static string seperator = "\r\n";
const static string headerEnd = "\r\n\r\n";

inline void Response::checkForHeader() {
    if (!header) {
        checkHeaderErrors();
        header = true;
        stringstream ss;
        ss << "HTTP/1.1 " << headerMap["Status"] << seperator;
        for (auto pair : headerMap) {
            string key = pair.first;
            
            if (key == "Status" || key == "Connection") {
                continue;
            }
            
            string value = pair.second;
            ss << key << ": " << value << seperator;
        }
        ss << "Connection" << ": " << headerMap["Connection"] << headerEnd;
        write(ss.str());
    }
}

void Response::write(const void* data, size_t size) {
    if (headerMap["Content-Length"] == "-1") {
        headerMap["Content-Length"] = (stringstream() << size).str();
    }
    checkForHeader();
    this->socket->write(data, size);
}

void Response::write(const string &data) {
    if (headerMap["Content-Length"] == "-1") {
        headerMap["Content-Length"] = (stringstream() << data.size()).str();
    }
    checkForHeader();
    this->socket->write(data.c_str(), data.size());
}

void Response::setHeader(string key, string value) {
    headerMap[key] = value;
}
