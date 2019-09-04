//
// Created by 方伟 on 2019-08-27.
//

#include "Buffer.h"
#include <errno.h>
#include <sys/uio.h>
#include <sys/types.h>

const size_t Buffer::kCheapPrepend;
const size_t Buffer::kInitialSize;

size_t Buffer::readFd(int fd, int *savedErrno) {
    char extrabuf[65536];
    struct iovec vec[2];
    const size_t writeable = writeablebytes();
    vec[0].iov_base = begin() + writeable;
    vec[0].iov_len = writeable;

    vec[1].iov_base = extrabuf;
    vec[1].iov_len = sizeof(extrabuf);
    const int iovcnt = (writeable < sizeof(extrabuf)) ? 2 : 1;
    const size_t n = ::readv(fd, vec, iovcnt);
    if (n < 0) {
        *savedErrno = errno;
    } else if (static_cast<size_t>(n) <= writeable) {
        writeIndex_ += n;
    } else {
        writeIndex_ = buffer_.size();
        append(extrabuf, n - writeable);
    }
    return n;
}