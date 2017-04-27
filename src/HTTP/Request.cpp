//
//  Request.cpp
//  Cpp_Server
//
//  Created by Mathias Tahas on 21.04.17.
//  Copyright © 2017 Mathias Tahas. All rights reserved.
//

#include "Request.hpp"

using namespace CppServer;

bool Request::headerEnded(string &head) {
    if (head.size() >= 4) {
        return head.compare(head.size() - 5, 4, "\r\n\r\n");
    }
    return false;
}

Request::Request(Socket* socket) {
    string receivedData;
    char buffer[BUFFER_SIZE];
    while (!headerEnded(receivedData)) {
        ssize_t nRead = socket->read(buffer, BUFFER_SIZE);
        receivedData += string(buffer, nRead);
    }
    this->requestHeader = receivedData;
    parse(socket);
}

inline string fetchLine(string header, string delim, size_t pos) {
    size_t next = header.find(delim, pos);
    return header.substr(pos, next - pos);
}

inline string findKey(string line) {
    size_t pos = line.find(": ");
    return line.substr(0, pos);
}

inline string findValue(string line, string key) {
    size_t len = key.length() + 2;
    return line.substr(len, line.size() - len);
}

inline string getFullPath(const string& requestHeader) {
    size_t first = requestHeader.find(" ");
    size_t second = requestHeader.find(" ", first + 1);
    return requestHeader.substr(first + 1, second - first - 1);
}

void Request::parse(Socket* socket) {
    string method = getMethod();
    string first = fetchLine(requestHeader, "\r\n", 0);
    parseHeader(requestHeader.substr(first.size() + 2, requestHeader.size() - first.size() - 1));
    if (method == "GET") {
        string fullPath = getFullPath(requestHeader);
        size_t pos = fullPath.find("?");
        if (pos != string::npos) {
            string params = fullPath.substr(pos + 1, fullPath.size() - pos - 1);
            parseParameters(params);
        }
    } else if (method == "POST") {
        size_t len = stol(headerMap["Content-Length"]);
        char *postData = new char[len];
        socket->read(postData, len);
        if (headerMap["Content-Type"] == "application/x-www-form-urlencoded") {
            parseParameters(string(postData, len));
            delete[] postData;
        }
    }
}

void Request::parseHeader(const string& header) {
    size_t pos = 0;
    string line;
    while (pos + 2 < header.size()) {
        line = fetchLine(header, "\r\n", pos);
        string key = findKey(line);
        string value = findValue(line, key);
        headerMap.insert(pair<string, string>(key, value));
        pos += line.size() + 2;
    }
}

void Request::parseParameters(const string& data) {
    string line;
    size_t pos = 0;
    while (pos < data.size()) {
        line = fetchLine(data, "&", pos);
        pos += line.size();
        size_t posOfDelim = line.find("=");
        string key = line.substr(0, posOfDelim);
        string value = line.substr(posOfDelim + 1, line.size() - 1);
        parameters.insert(pair<string, string>(key, value));
    }
}

string& Request::getPath() {
    if (path.empty()) {
        path = getFullPath(requestHeader);
        size_t pos = path.find("?");
        if(pos < path.size()) {
            path = path.substr(0, pos);
        }
    }
    return path;
}

string& Request::getMethod() {
    if (method.empty()) {
        size_t first = requestHeader.find(" ");
        method = requestHeader.substr(0, first);
    }
    return method;
}
