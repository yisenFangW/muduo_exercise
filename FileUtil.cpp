//
// Created by 方伟 on 2019-09-02.
//

#include "FileUtil.h"

FileUtil::AppendFile::AppendFile(FileUtil::StringArg filename)
        : fp_(::fopen(filename.c_str(), "ae")),
          writtenBytes_(0) {
    ::setbuffer(fp_, buffer_, sizeof(buffer_));
}

FileUtil::AppendFile::~AppendFile() {
    ::fclose(fp_);
}

void FileUtil::AppendFile::append(const char *logline, size_t len) {
    size_t n = write(logline, len);
    size_t remain = len - n;
    while (remain > 0) {
        size_t x = write(logline + n, remain);
        if (x == 0) {
            int err = ferror(fp_);
            if (err) {
                fprintf(stderr, "AppendFile::append() fiiled %s\n", stderror_r(err));
            }
            break;
        }
        n += x;
        remain = len - n;
    }
    writtenBytes_ += len;
}

void FileUtil::AppendFile::flush() {
    ::fflush(fp_);
}

