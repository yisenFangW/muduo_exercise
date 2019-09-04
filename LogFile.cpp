//
// Created by 方伟 on 2019-09-02.
//

#include "LogFile.h"
#include "FileUtil.h"

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

void LogFile::rollFile() {

}

const string getLogFileName(const string &basename, time_t time) {
    string filename = string();
    filename.reserve(basename.size() + 64);
    filename = basename;

}

void LogFile::append_unlock(const char *logline, int len) {

}
