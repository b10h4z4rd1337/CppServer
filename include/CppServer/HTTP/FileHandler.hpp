//
//  FileHandler.hpp
//  Cpp_Server
//
//  Created by Mathias Tahas on 22.04.17.
//  Copyright © 2017 Mathias Tahas. All rights reserved.
//

#ifndef FileHandler_hpp
#define FileHandler_hpp

#include "Request.hpp"
#include "Response.hpp"

#include <string>

using namespace std;

namespace CppServer {
    class FileHandler {
        
    private:
        string mimeType;
        const string fileName;
        shared_ptr<char> data;
        size_t size = -1;
        
        void load();
        
    public:
        FileHandler(const string& fileName, bool cache = true);
        const string getPath() const;
        
        void operator ()(Request& req, Response& res);
    };
}

#endif /* FileHandler_hpp */
