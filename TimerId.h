//
// Created by 方伟 on 2019-08-24.
//

#ifndef CLIENT_TIMERID_H
#define CLIENT_TIMERID_H

// 因为在这个函数中，Timer这个类的只用到了声明为指针的用法，所以
// 这个类是这么写的，他并没有包括timer.h这个头文件，而是将Timer这个类声明出来直接用；
// 注意这种用法，这种用法的好处是什么？？wefang
// #include "timer.h"

#include <cstdint>

class Timer;

class TimerId{
public:
    TimerId()
        :timer_(nullptr),
        sequence_(0){
    }

    TimerId(Timer *timer, int64_t sequence)
        :timer_(timer),
        sequence_(sequence){
    }

    friend class TimerQueue;

private:
    Timer *timer_;
    int64_t sequence_;
};




#endif //CLIENT_TIMERID_H
