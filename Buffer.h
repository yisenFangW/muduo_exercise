//
// Created by 方伟 on 2019-08-27.
//

#ifndef CLIENT_BUFFER_H
#define CLIENT_BUFFER_H

#include <vector>
#include <assert.h>
#include <string>

class Buffer {
public:
    static const size_t kCheapPrepend = 8;
    static const size_t kInitialSize = 1024;

    explicit Buffer(size_t initialSize = kInitialSize)
            : buffer_(kCheapPrepend + initialSize),
              readerIndex_(kCheapPrepend),
              writeIndex_(kCheapPrepend) {
        assert(readablebytes() == 0);
        assert(writeablebytes() == initialSize);
        assert(prependablebytes() == readerIndex_);
    }

    size_t readablebytes() { return readerIndex_ - kCheapPrepend; }

    size_t writeablebytes() { return buffer_.size() - writeIndex_; }

    size_t prependablebytes() { return readerIndex_; }

    const char *peek() { return begin() + readerIndex_; }

    void retrive(size_t len) {
        assert(len <= readablebytes());
        if (len < readablebytes())
            readerIndex_ += len;
        else
            retriveAll();
    }

    void retriveAll() {
        readerIndex_ = kCheapPrepend;
        writeIndex_ = kCheapPrepend;
    }

    void ensureWriteableBytes(size_t len) {
        if (writeablebytes() < len)
            makeSpace(len);
        assert(writeablebytes() >= len);
    }

    void append(const char *data, size_t len) {
        ensureWriteableBytes(len);
        std::copy(data, data + len, begin() + writeIndex_);
        hasWritten(len);
    }

    void hasWritten(size_t len) {
        assert(len <= writeablebytes());
        writeIndex_ += len;
    }

    void shrink(size_t reserve) {
        Buffer other;
        other.ensureWriteableBytes(readablebytes() + reserve);
        other.append(begin() + readerIndex_, readablebytes());
        swap(other);
    }

    void swap(Buffer &bf) {
        std::swap(buffer_, bf.buffer_);
        std::swap(readerIndex_, bf.readerIndex_);
        std::swap(writeIndex_, bf.writeIndex_);
    }

    size_t internalCapacity() const {
        return buffer_.capacity();
    }

    /// Read data directly into buffer.
    ///
    /// It may implement with readv(2)
    /// @return result of read(2), @c errno is saved
    size_t readFd(int fd, int *savedErrno);

private:
    // 注意这个begin()的返回，是返回一个buffer_.begin()的地址；
    char *begin() { return &*buffer_.begin(); }

    void makeSpace(size_t len) {
        // 如果连前面读预留空间加起来都不够的话，就直接分配新的空间；
        if (writeablebytes() + prependablebytes() < len + kCheapPrepend) {
            buffer_.resize(writeIndex_ + len);
        } else {
            // 如果加上读预留空间够的话，调整下分配的位置；
            assert(kCheapPrepend < readerIndex_);
            size_t readable = readablebytes();
            std::copy(begin() + readerIndex_,
                      begin() + writeIndex_,
                      begin() + kCheapPrepend);
            readerIndex_ = kCheapPrepend;
            writeIndex_ = kCheapPrepend + readable;
        }
    }

private:
    std::vector<char> buffer_;
    size_t readerIndex_;
    size_t writeIndex_;
};


#endif //CLIENT_BUFFER_H
