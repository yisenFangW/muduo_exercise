//
// Created by 方伟 on 2019-08-24.
//

#ifndef CLIENT_MUTEXLOCKGUARD_H
#define CLIENT_MUTEXLOCKGUARD_H

#include <mutex>
#include <pthread.h>


// RAII思想？构造，析构函数中加锁解锁
class MutexLockGuard{
public:
    MutexLockGuard(){
        pthread_mutex_lock(&mutex);
    }

    ~MutexLockGuard(){
        pthread_mutex_unlock(&mutex);
    }

private:
    pthread_mutex_t mutex;
};

#endif //CLIENT_MUTEXLOCKGUARD_H
