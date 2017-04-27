# CppServer
A simple and easy to use server framework inspired by node.js / express written in C++ for maximum performance, low memory footprint and scalability.

Creating a server is simple:

```C++
#include <HTTP/HTTPServer.hpp>              //include HTTPServer header

using namespace CppServer;                  //Bring in the namespace

int main(int argc, const char * argv[]) {
    HTTPServer server(1337);                //Create Server Object
    server.addRoute("GET", "/",             //Add a route to '/' with GET
        [](Request& req, Response& res) {   //Provide a lambda, which defines routes behaviour
            res.write("Hello World");       //Write 'Hello World to the response'
        });
    server.start();                         //Start infinite server loop
    return 0;
}
```

This project is in early aplha and I would be happy if you could contribute and comment, to make this framework reasonbly working.

Currently following features are supported:

- Handle GET and POST requests
- Automatically parse POST requests to HTML Documents
- Provide files
