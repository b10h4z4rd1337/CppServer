//
//  ThreadPool.hpp
//  Cpp_Server
//
//  Created by Mathias Tahas on 25.04.17.
//  Copyright © 2017 Mathias Tahas. All rights reserved.
//

#ifndef ThreadPool_hpp
#define ThreadPool_hpp

#include <thread>
#include <queue>
#include <vector>

using namespace std;

namespace CppServer {
    typedef function<void()> func;
    
    class ThreadPool {
    public:
        ThreadPool(int numOfThreads = thread::hardware_concurrency());
        ~ThreadPool();
        void appendJob(const func& f);
        void threadEntry();
        
    private:
        mutex lock;
        condition_variable condVar;
        bool shutdown = false;
        queue<func> workQueue;
        vector<thread> threadList;
    };
}

#endif /* ThreadPool_hpp */
