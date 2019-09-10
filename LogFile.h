//
// Created by 方伟 on 2019-09-02.
//

#ifndef CLIENT_LOGFILE_H
#define CLIENT_LOGFILE_H

#include <time.h>
#include <stdio.h>
#include <iostream>
#include <string>
#include "MutexLockGuard.h"
#include "FileUtil.h"
#include <memory>
#include <Mutex>

using std::string;

class LogFile {
public:
    LogFile(const string &filename,
            off_t rollSize,
            //bool threadSafe = true,
            int flushInterval = 3,
            int checkEveryN = 1024);

    ~LogFile() {}

    void append(const char *logline, int len);

    void flush();

     bool rollFile();

private:
    void append_unlock(const char *logline, int len);

    const string getLogFileName(const string& basename, time_t time);

private:
    const string basename_;

    const off_t rollSize_;

    const int flushInterval_;

    const int checkEveryN_;

    int count_;

    //std::unique_ptr<MutexLock> mutex_;

    time_t startOfPeriod_;

    time_t lastRoll_;

    time_t lastFlush_;

    std::unique_ptr<FileUtil::AppendFile> file_;

    const static int kRollPerSeconds_ = 60 * 60 * 24;
};


#endif //CLIENT_LOGFILE_H
