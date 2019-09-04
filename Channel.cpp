//
// Created by 方伟 on 2019-08-29.
//

#include "Channel.h"
#include <poll.h>
#include <iostream>
#include <string>

// 这个函数没有写全，需要写全才行；

const int Channel::kNoneEvent = 0;
const int Channel::kReadEvent = POLLIN | POLLPRI;
const int Channel::kWriteEvent = POLLOUT;

Channel::Channel(EventLoop *loop, int fd)
        : fd_(fd),
          index_(-1),
          event_(0),
          revents_(0),
          loop_(loop),
          addedToLoop_(false),
          logHup_(false),
          eventHandling_(false) {

}

void Channel::remove() {
    addedToLoop_ = false;
    //loop_.removeChannel(this);
}

void Channel::update() {
    addedToLoop_ = true;
    //loop_.updateChannel(this);
}

void Channel::handleEventWithGuard(Timestamp receiveTime) {
    eventHandling_ = true;   // 事件处理标志
    //LOG_TRACE << reventsToString();
    if ((revents_ & POLLHUP) && !(revents_ & POLLIN)) {
        // logHup_用于标志与POLLHUP有关的内容；
        if (logHup_) {
            // LOG_WARN << "fd = " << fd_ << " Channel::handle_event() POLLHUP";
        }
        if (closeCallback_) closeCallback_();
    }

    if (revents_ & POLLNVAL) {
        // LOG_WARN << "fd = " << fd_ << " Channel::handle_event() POLLNVAL";
    }

    if (revents_ & (POLLERR | POLLNVAL)) {
        if (errorCallback_) errorCallback_();
    }
    if (revents_ & (POLLIN | POLLPRI | POLLRDHUP)) {
        if (readCallback_) readCallback_(receiveTime);
    }
    if (revents_ & POLLOUT) {
        if (writeCallback_) writeCallback_();
    }
    eventHandling_ = false;
}

std::string Channel::eventsToString() const {
    return eventsToString(fd_, events_);
}

std::string Channel::reventsToString() const {
    return eventsToString(fd_, revents_);
}

std::string Channel::eventsToString(int fd, int ev) const {
    std::cout << "fd:" << fd << std::endl;
    std::string res = std::string();
    if (ev & POLLIN)
        res += "IN ";
    if (ev & POLLPRI)
        res += "PRI ";
    if (ev & POLLOUT)
        res += "OUT ";
    if (ev & POLLHUP)
        res += "HUP ";
    if (ev & POLLRDHUP)
        res += "RDHUP ";
    if (ev & POLLERR)
        res += "ERR ";
    if (ev & POLLNVAL)
        res += "NVAL ";
}
