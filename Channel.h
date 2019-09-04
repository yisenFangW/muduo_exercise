//
// Created by 方伟 on 2019-08-29.
//

#ifndef CLIENT_CHANNEL_H
#define CLIENT_CHANNEL_H

#include "Timestamp.h"

class Channel {
    class EventLoop;

public:
    typedef std::function<void()> EventCallBack;
    typedef std::function<void(Timestamp)> ReadCallBack;

    static const int kNoneEvent;
    static const int kReadEvent;
    static const int kWriteEvent;

    explicit Channel(EventLoop *loop, int fd);

    void set_revents(int revents) { revents_ = revents; }

    bool isNoneEvent() const { return events_ == kNoneEvent; }

    // 改变了监听文件描述符要监听的事件类型，更新下监听的channel,下面也是一样的；
    void enableReading() {
        events_ |= kReadEvent;
        update();
    }

    void disableReading() {
        events_ &= ~kReadEvent;
        update();
    }

    void enableWriting() {
        events_ |= kWriteEvent;
        update();
    }

    void disableWriting() {
        events_ &= ~kWriteEvent;
        update();
    }

    // 将事件变成不关注
    void disableAll() {
        events_ = kNoneEvent;
        update();
    }

    bool isWriting() const { return events_ & kWriteEvent; }

    bool isReading() const { return events_ & kReadEvent; }

    int index() { return index_; }

    void setindex(int index) { index_ = index; }

    EventLoop *ownloop() { return loop_; }

    // 用move更快一点，省去了一次复制的过程
    void setReadCallBack(ReadCallBack cb) { readCallBack_ = std::move(cb); }

    void setWriteCallBack(EventCallBack cb) { writeCallBack_ = std::move(cb); }

    void setCloseCallBack(EventCallBack cb) { closeCallBack_ = std::move(cb); }

    void setErrorCallBack(EventCallBack cb) { errorCallBack_ = std::move(cb); }

    int fd() { return fd_; }

    int event() { return event_; }

    void remove();

    std::string eventsToString() const;

    std::string reventsToString() const;

private:
    void update();

    std::string eventsToString(int fd, int ev) const;

    void handleEventWithGuard(Timestamp receiveTime);

private:
    int fd_;
    int event_;
    int events_;
    int revents_;
    int index_;
    int addedToLoop_;
    bool logHup_;
    bool eventHandling_;

    EventLoop *loop_;

    ReadCallBack readCallback_;
    EventCallBack writeCallback_;
    EventCallBack closeCallback_;
    EventCallBack errorCallback_;
};


#endif //CLIENT_CHANNEL_H
