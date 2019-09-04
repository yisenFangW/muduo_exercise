//
// Created by 方伟 on 2019-08-23.
//

#ifndef CLIENT_TIMER_H
#define CLIENT_TIMER_H

#include <iostream>
#include "Timestamp.h"

class Timer {
public:
    typedef std::function<void()> Timecallback;

    Timer(Timecallback cb, Timestamp when, double interval):
        callback_(std::move(cb)),
        expiration_(when),
        interval_(interval),
        repeat_(interval > 0.0),
        sequence_(incrementAndGet()){}

    void run() const{
        callback_();
    }

    void restart(Timestamp now);

    Timestamp expiration(){return expiration_;}

    bool repeat() const{return repeat_;}

    int64_t incrementAndGet(){
        return ++numCreated_;
    }

private:
    Timestamp expiration_;    // 什么时候发生
    double interval_;         // 间隔，判断是否循环
    bool repeat_;             // interval_>0 说明循环
    Timecallback callback_;   // 时间到了的回调函数
    const int sequence_;      // 第几次重复；

    int64_t numCreated_;
};


#endif //CLIENT_TIMER_H
