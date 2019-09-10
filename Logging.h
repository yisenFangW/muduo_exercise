//
// Created by 方伟 on 2019-09-01.
//

#ifndef CLIENT_LOGGING_H
#define CLIENT_LOGGING_H

#include <stdio.h>
#include <string>
#include "LogStream.h"
#include "Timestamp.h"


class Logger {
public:
    // 日志的粒度，调试一般用debug，运行过程中调试打印的内容太多了，一般使用info作为日常使用的打印
    // warn是警告，error是报错，fatal直接就让程序崩啦；
    // 用NUM_LOG_LEVELS来标志着log的粒度到底有多少个；
    enum LogLevel {
        TRACE,
        DEBUG,
        INFO,
        WARN,
        ERROR,
        FATAL,
        NUM_LOG_LEVELS,
    };

    // compile time calculation of basename of source file
    class SourceFile {
    public:
        template<int N>
        SourceFile(const char (&arr)[N])
                : data_(arr),
                  size_(N - 1) {
            // C 库函数 char *strrchr(const char *str, int c) 在参数 str 所指向的字符串
            // 中搜索最后一次出现字符 c（一个无符号字符）的位置。
            // 返回值是最后一次出现c的位置，若找不到则返回一个空指针
            const char *slash = strrchr(data_, '/'); // builtin function
            if (slash) {
                data_ = slash + 1;
                size_ -= static_cast<int>(data_ - arr);
            }
        }

        //一般都是用这个功能的把，传入一个日志的地址
        explicit SourceFile(const char *filename)
                : data_(filename) {
            // char *strrchr(const char *str, int c)
            // 在参数 str 所指向的字符串中搜索最后一次出现字符 c（一个无符号字符）的位置
            // 找到一个日志的最深处的目录
            const char *slash = strrchr(filename, '/');
            if (slash) {
                data_ = slash + 1;
            }
            size_ = static_cast<int>(strlen(data_));
        }

        const char *data_;
        int size_;
    };

    Logger(SourceFile file, int line);

    Logger(SourceFile file, int line, LogLevel level);

    Logger(SourceFile file, int line, LogLevel level, const char *func);

    Logger(SourceFile file, int line, bool toAbort);

    ~Logger();

    // stream使用的是impl对象返回LogStream
    LogStream &stream() { return impl_.stream_; }

    static LogLevel logLevel();

    static void setLogLevel(LogLevel level);

    typedef void (*OutputFunc)(const char *msg, int len);

    typedef void (*FlushFunc)();

    static void setOutput(OutputFunc);

    static void setFlush(FlushFunc);

    static void setTimeZone(const TimeZone &tz);

private:

    class Impl {
    public:
        typedef Logger::LogLevel LogLevel;

        //日志的实际实现，格式化日志内容；
        Impl(LogLevel level, int old_errno, const SourceFile &file, int line);

        void formatTime();

        void finish();

        Timestamp time_;
        //LogStream放在Impl函数中作为一个对象成员使用
        LogStream stream_;
        LogLevel level_;
        int line_;
        SourceFile basename_;
    };

    Impl impl_;

};

extern Logger::LogLevel g_logLevel;

inline Logger::LogLevel Logger::logLevel() {
    return g_logLevel;
}


#define LOG_TRACE if (muduo::Logger::logLevel() <= muduo::Logger::TRACE) \
  muduo::Logger(__FILE__, __LINE__, muduo::Logger::TRACE, __func__).stream()
#define LOG_DEBUG if (muduo::Logger::logLevel() <= muduo::Logger::DEBUG) \
  muduo::Logger(__FILE__, __LINE__, muduo::Logger::DEBUG, __func__).stream()
#define LOG_INFO if (muduo::Logger::logLevel() <= muduo::Logger::INFO) \
  muduo::Logger(__FILE__, __LINE__).stream()
#define LOG_WARN muduo::Logger(__FILE__, __LINE__, muduo::Logger::WARN).stream()
#define LOG_ERROR muduo::Logger(__FILE__, __LINE__, muduo::Logger::ERROR).stream()
#define LOG_FATAL muduo::Logger(__FILE__, __LINE__, muduo::Logger::FATAL).stream()
#define LOG_SYSERR muduo::Logger(__FILE__, __LINE__, false).stream()
#define LOG_SYSFATAL muduo::Logger(__FILE__, __LINE__, true).stream()


#endif //CLIENT_LOGGING_H
