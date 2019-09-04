//
// Created by 方伟 on 2019-08-23.
//

#ifndef CLIENT_TIMESTAMP_H
#define CLIENT_TIMESTAMP_H

#include <iostream>
#include <cstdint>
#include <sys/time.h>

class Timestamp {
public:
    static const int kMicroSecondsPerSecond = 1000 * 1000;

    Timestamp():microSecondsSinceEpoch_(0){}

    explicit Timestamp(int64_t microSecondsSinceEpoch)
            :microSecondsSinceEpoch_(microSecondsSinceEpoch){}

    std::string toString();

    std::string formatToString();

    bool valid(){
        return microSecondsSinceEpoch_ > 0;
    }

    int64_t microSecondsSinceEpoch(){
        return microSecondsSinceEpoch_;
    }

    static Timestamp now();

    Timestamp invalid(){
        return Timestamp();
    }

    Timestamp swap(Timestamp& t){
        std::swap(t.microSecondsSinceEpoch_, microSecondsSinceEpoch_);
    }

private:
    int64_t microSecondsSinceEpoch_;
};

inline double timeDifference(Timestamp high, Timestamp low){
    int64_t diff = high.microSecondsSinceEpoch() - low.microSecondsSinceEpoch();
    return static_cast<double>(diff) / Timestamp::kMicroSecondsPerSecond;
}


inline Timestamp addTimer(Timestamp timestamp, double seconds){
    int64_t delta = static_cast<int64_t >(seconds * Timestamp::kMicroSecondsPerSecond);
    return Timestamp(timestamp.microSecondsSinceEpoch() + delta);
}

#endif //CLIENT_TIMESTAMP_H
