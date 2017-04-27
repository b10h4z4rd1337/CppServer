//
//  FileIO.cpp
//  Cpp_Server
//
//  Created by Mathias Tahas on 23.04.17.
//  Copyright © 2017 Mathias Tahas. All rights reserved.
//

#include "FileIO.hpp"

#include <fstream>

using namespace CppServer;

size_t FileIO::getFileSize(const string &path) {
    ifstream stream(path, ios::binary | ios::ate);
    return stream.tellg();
}

char* FileIO::loadFile(const string &path, size_t size) {
    char* result = new char[size];
    
    ifstream stream(path, ios::binary);
    stream.read(result, size);
    
    return result;
}

string FileIO::getMIMEtype(const string &path) {
    string data = "";
    char buffer[128];
    FILE* pipe = popen((string("file --mime ") + path).c_str(), "r");
    size_t nRead;
    while ((nRead = fread(buffer, sizeof(char), sizeof(buffer), pipe))) {
        data += string(buffer, nRead);
    }
    fclose(pipe);
    
    unsigned long pos1 = data.find(": ") + 1;
    return string(data.substr(pos1, data.find(";") - pos1));
}

string* FileIO::loadFile(const string& path) {
    size_t size = getFileSize(path);
    char* data = loadFile(path, size);
    
    string* result = new string(data, size);
    
    delete[] data;
    return result;
}
