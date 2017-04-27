//
//  FileIO.hpp
//  Cpp_Server
//
//  Created by Mathias Tahas on 23.04.17.
//  Copyright © 2017 Mathias Tahas. All rights reserved.
//

#ifndef FileIO_hpp
#define FileIO_hpp

#include <string>

using namespace std;

namespace CppServer {
    namespace FileIO {
        size_t getFileSize(const string& path);
        char* loadFile(const string& path, size_t size);
        string getMIMEtype(const string& path);
        
        string* loadFile(const string& path);
    }
}

#endif /* FileIO_hpp */
