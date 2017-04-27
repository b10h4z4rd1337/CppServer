//
//  Parser.hpp
//  Cpp_Server
//
//  Created by Mathias Tahas on 25.04.17.
//  Copyright © 2017 Mathias Tahas. All rights reserved.
//

#ifndef Parser_hpp
#define Parser_hpp

#include <map>
#include <string>

using namespace std;

namespace CppServer {
    namespace Parser {
        string parse(const string& input, const map<string, string>& inMap);
    }
}

#endif /* Parser_hpp */
