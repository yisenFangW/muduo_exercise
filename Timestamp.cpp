//
// Created by 方伟 on 2019-08-23.
//

#include "Timestamp.h"
#include "client.h"

std::string Timestamp::toString(){
    int64_t seconds = microSecondsSinceEpoch_ / kMicroSecondsPerSecond;
    int64_t useconds = microSecondsSinceEpoch_ % kMicroSecondsPerSecond;
    std::cout<< seconds << useconds << std::endl;
 }

std::string Timestamp::formatToString(){
    return std::string();
}

Timestamp Timestamp::now(){
    struct timeval tv;
    gettimeofday(&tv, NULL);
    int64_t seconds = tv.tv_sec;
    return Timestamp(seconds*kMicroSecondsPerSecond + tv.tv_usec);
}