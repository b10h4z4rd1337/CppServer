//
//  Parser.cpp
//  Cpp_Server
//
//  Created by Mathias Tahas on 25.04.17.
//  Copyright © 2017 Mathias Tahas. All rights reserved.
//

#include "Parser.hpp"

using namespace CppServer;

string Parser::parse(const string &input, const map<string, string>& inMap) {
    string data = input;
    for (auto it : inMap) {
        string key = "{" + it.first + "}";
        string value = it.second;
        
        string::size_type pos = 0;
        while ((pos = data.find(key, pos)) != string::npos) {
            data.replace(pos, key.size(), value);
            pos += value.size();
        }
    }
    return data;
}
