//
// Created by 方伟 on 2019-09-02.
//

#ifndef CLIENT_FILEUTIL_H
#define CLIENT_FILEUTIL_H

#include <string>

using std::string;

class FileUtil {
    class StringArg // copyable
    {
    public:
        StringArg(const char *str)
                : str_(str) {}

        StringArg(const string &str)
                : str_(str.c_str()) {}

        const char *c_str() const { return str_; }

    private:
        const char *str_;
    };

    public:
    class AppendFile {
    public:
        explicit AppendFile(StringArg filename);

        ~AppendFile();

        void append(const char *logline, size_t len);

        void flush();

        off_t writtenBytes() { return writtenBytes_; }

    private:
        size_t write(const char *logline, size_t len);

        FILE *fp_;

        char buffer_[64 * 1024];

        off_t writtenBytes_;
    };


};


#endif //CLIENT_FILEUTIL_H
