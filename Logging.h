//
// Created by 方伟 on 2019-09-01.
//

#ifndef CLIENT_LOGGING_H
#define CLIENT_LOGGING_H

#include <stdio.h>
#include <string>
#include "LogStream.h"

class Logging {
public:
    // 辅助类，取文件名的最后一个后缀
    class SourceFile{
        SourceFile(const char* filename):
            data_(filename){
            const char* slash = strrchr(data_, '/');
            if(slash) {
                data_ = slash + 1;
            }
            size_ = static_cast<size_t >(strlen(data_));

        }
    private:
        const char *data_;
        size_t size_;
    };

private:



};


#endif //CLIENT_LOGGING_H
