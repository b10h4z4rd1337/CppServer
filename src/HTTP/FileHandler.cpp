//
//  FileHandler.cpp
//  Cpp_Server
//
//  Created by Mathias Tahas on 22.04.17.
//  Copyright © 2017 Mathias Tahas. All rights reserved.
//

#include "FileHandler.hpp"
#include "FileIO.hpp"

using namespace CppServer;
using namespace FileIO;

#include <sstream>

FileHandler::FileHandler(const string& fN, bool cache) : fileName(fN) {
    if (cache) {
        load();
    }
}

void FileHandler::load() {
    size = getFileSize(fileName);
    mimeType = getMIMEtype(fileName);
    data = shared_ptr<char>(loadFile(fileName, size));
}

const string FileHandler::getPath() const {
    return string("/").append(fileName);
}

void FileHandler::operator()(Request &req, Response &res) {
    if (!data) {
        load();
    }
    
    res.setHeader("Status", "200 OK");
    res.setHeader("Content-Type", mimeType);
    res.setHeader("Content-Length", (stringstream() << size).str());
    
    res.write(data.get(), size);
}
