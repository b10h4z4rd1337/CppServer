//
//  HTMLDocument.cpp
//  Cpp_Server
//
//  Created by Mathias Tahas on 22.04.17.
//  Copyright © 2017 Mathias Tahas. All rights reserved.
//

#include "HTMLDocument.hpp"
#include "FileIO.hpp"
#include "Parser.hpp"

#include <sstream>

using namespace CppServer;
using namespace FileIO;

HTMLDocument HTMLDocument::fromFile(const string &fileName) {
    return HTMLDocument(loadFile(fileName));
}

HTMLDocument HTMLDocument::fromString(const string &html) {
    return HTMLDocument(new string(html));
}

HTMLDocument::HTMLDocument(string* html) : html(shared_ptr<string>(html)), size(html->size()) {
    fileHandles = shared_ptr<vector<FileHandler>>(new vector<FileHandler>());
    vector<string> *res = parseRessources(*html);
    loadRessources(res);
    delete res;
}

void HTMLDocument::setAutoParsePostParamters(bool b) {
    this->autoParse = b;
}

vector<string>* HTMLDocument::parseRessources(const string& html) {
    vector<string> *result = new vector<string>;
    size_t pos = 0;
    while ((pos = html.find("src=", pos)) != string::npos) {
        pos += 5;
        size_t len = html.find(" ", pos + 1) - pos - 1;
        result->push_back(html.substr(pos, len));
    }
    return result;
}

void HTMLDocument::loadRessources(vector<string> *files) {
    for (auto name : *files) {
        FileHandler handler(name);
        fileHandles->push_back(handler);
    }
}

void HTMLDocument::operator()(Request &req, Response &res) {
    string html = *(this->html);
    if (autoParse) {
        html = Parser::parse(html, req.parameters);
    }
    res.setHeader("Content-Type", "text/html");
    res.setHeader("Content-Length", (stringstream() << html.size()).str());
    res.write(html);
}
