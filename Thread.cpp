//
// Created by 方伟 on 2019-09-09.
//

#include "Thread.h"

struct ThreadData {
    typedef Thread::ThreadFunc ThreadFunc;
    ThreadFunc func_;
    string name_;
    pid_t *tid_;

    ThreadData(ThreadFunc func,
               const string &name,
               pid_t *tid) :
            func_(std::move(func)),
            name_(name),
            tid_(tid) {
    }

    void runInThread() {
        func_();
    }
};

void *startThread(void *obj) {
    ThreadData *data = static_cast<ThreadData *>(obj);
    data->runInThread();
    delete data;
    return NULL;
}

Thread::Thread(ThreadFunc func, const string &name)
        : started_(false),
          joined_(false),
          pthreadId_(0),
          tid_(0),
          func_(std::move(func)),
          name_(name) {
    setDefaultName();
}

Thread::~Thread() {
    if(started_ && !joined_)
        pthread_detach(pthreadId_);
}

void Thread::start() {
    started_ = true;
    ThreadData *data = new ThreadData(func_, name_, &tid_);
    if(pthread_create(&pthreadId_, NULL, &startThread, data)){
        started_ = false;
        delete data;
    }
}

int Thread::join() {
    joined_ = true;
    return pthread_join(pthreadId_, NULL);
}

string Thread::setDefaultName() {
    int num = numCreated_.incrementAndGet();
    if (name_.empty()) {
        char buf[32];
        snprintf(buf, sizeof(buf), "Thread%d", num);
        name_ = buf;
    }
}
