//
// Created by 方伟 on 2019-09-01.
//

#include "Logging.h"


Logger::Logger(Logger::SourceFile file, int line)
        : impl_(INFO, 0, file, line) {

}

