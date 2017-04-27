//
//  ThreadPool.cpp
//  Cpp_Server
//
//  Created by Mathias Tahas on 25.04.17.
//  Copyright © 2017 Mathias Tahas. All rights reserved.
//

#include "ThreadPool.hpp"

using namespace CppServer;

ThreadPool::ThreadPool(int numOfThreads) {
    for (int i = 0; i < numOfThreads; i++) {
        threadList.push_back(thread(&ThreadPool::threadEntry, this));
    }
}

ThreadPool::~ThreadPool() {
    unique_lock<mutex> l(lock);
    
    shutdown = true;
    condVar.notify_all();
    
    for (auto& thread : threadList)
        thread.join();
}

void ThreadPool::threadEntry() {
    func f;
    unique_lock<mutex> l(lock);
    
    while (!shutdown && workQueue.empty()) {
        condVar.wait(l);
    }
    
    if (workQueue.empty()) {
        return;
    }
    
    f = move(workQueue.front());
    workQueue.pop();
    
    f();
}

void ThreadPool::appendJob(const func &f) {
    unique_lock<mutex> l(lock);
    
    workQueue.emplace(move(f));
    condVar.notify_one();
}
