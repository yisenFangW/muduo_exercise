//
// Created by 方伟 on 2019-09-09.
//

#ifndef CLIENT_THREAD_H
#define CLIENT_THREAD_H

#include <functional>
#include <memory>
#include <string>
#include <pthread.h>
#include "Atomic.h"

using std::string;

class Thread {
public:
    typedef std::function<void()> ThreadFunc;

    Thread(ThreadFunc, const string &name = string());

    ~Thread();

    void start();

    int join();

    bool started(){return started_;}

    pid_t tid(){return tid_;}

    const string& name(){return name_;}

private:
    string setDefaultName();

private:
    bool started_;
    bool joined_;
    pthread_t pthreadId_;
    pid_t tid_;
    ThreadFunc func_;
    string name_;
    static AtomicInt32 numCreated_;
};


#endif //CLIENT_THREAD_H
