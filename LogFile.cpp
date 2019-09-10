//
// Created by 方伟 on 2019-09-02.
//

#include "LogFile.h"
#include <unistd.h>
#include <time.h>

static const int kRollPerSeconds_ = 1000;

LogFile::LogFile(const string &filename,
                 off_t rollSize,
        //bool threadSafe,
                 int flushInterval,
                 int checkEveryN) :
        basename_(filename),
        rollSize_(rollSize),
        count_(0),
        flushInterval_(flushInterval),
        checkEveryN_(checkEveryN),
        startOfPeriod_(0),
        lastFlush_(0),
        lastRoll_(0) {

}

void LogFile::append(const char *logline, int len) {
    // 现在写先不考虑线程问题；
    append_unlock(logline, len);
}

void LogFile::flush() {
    // 现在写先不考虑线程问题；
    file_->flush();
}

bool LogFile::rollFile() {
    time_t now = 0;
    string filename = getLogFileName(basename_, now);
    time_t start = now / kRollPerSeconds_ * kRollPerSeconds_;

    if(now > lastRoll_){
        lastRoll_ = now;
        lastFlush_ = now;
        startOfPeriod_ = start;
        file_.reset(new FileUtil::AppendFile(filename));
        return true;
    }
    return false;
}

const string getLogFileName(const string &basename, time_t *now) {
    string filename = string();
    filename.reserve(basename.size() + 64);
    filename = basename;
    struct tm tm;
    char timebuf[32];
    *now = time(nullptr);
    gmtime_r(now, &tm);
    strftime(timebuf, sizeof(timebuf), "%Y%m%d-%H:%M:%S.", &tm);
    filename += timebuf;
    char pidbuf[32];
    snprintf(pidbuf, sizeof(pidbuf), "%d", ::getpid());
    filename += pidbuf;
    filename += ".log";
    return filename;
}

void LogFile::append_unlock(const char *logline, int len) {

}
