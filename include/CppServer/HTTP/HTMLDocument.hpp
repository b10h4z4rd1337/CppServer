//
//  HTMLDocument.hpp
//  Cpp_Server
//
//  Created by Mathias Tahas on 22.04.17.
//  Copyright © 2017 Mathias Tahas. All rights reserved.
//

#ifndef HTMLDocument_hpp
#define HTMLDocument_hpp

#include "FileHandler.hpp"

#include <string>
#include <vector>

using namespace std;

namespace CppServer {
    class HTMLDocument {
        friend class HTTPServer;
        
    public:
        static HTMLDocument fromFile(const string& fileName);
        static HTMLDocument fromString(const string& html);
        
        void operator ()(Request& req, Response& resp);
        
        void setAutoParsePostParamters(bool b);
        
    private:
        HTMLDocument(string* html);
        void setServer(HTTPServer* server);
        
        static vector<string>* parseRessources(const string& html);
        void loadRessources(vector<string> *files);
        
        shared_ptr<vector<FileHandler>> fileHandles;
        shared_ptr<string> html;
        size_t size;
        bool autoParse = false;
    };
}

#endif /* HTMLDocument_hpp */
