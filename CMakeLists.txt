cmake_minimum_required(VERSION 3.14)
project(client)

set(CMAKE_CXX_STANDARD 14)

add_executable(client main.cpp client.cpp client.h Timestamp.cpp Timestamp.h Timer.cpp Timer.h TimerId.h MutexLockGuard.h TimerQueue.cpp TimerQueue.h Buffer.cpp Buffer.h Channel.cpp Channel.h Logging.cpp Logging.h LogStream.cpp LogStream.h LogFile.cpp LogFile.h FileUtil.cpp FileUtil.h Thread.cpp Thread.h Atomic.h)