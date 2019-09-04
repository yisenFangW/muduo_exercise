//
// Created by 方伟 on 2019-08-23.
//

#include "Timer.h"

void Timer::restart(Timestamp now){
   if(repeat_)
       expiration_ = addTimer(now, interval_);
   else
       expiration_ = now.invalid();
}