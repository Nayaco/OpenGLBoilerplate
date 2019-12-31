//
// Created by Henry Little on 2019/9/15.
//

#include <iostream>
#include <cstring>
#include "ByteBuffer.h"

ByteBuffer::ByteBuffer(unsigned int byteCount) {
    buffer = new unsigned char[byteCount];
    offset = 0;
    bufferSize = byteCount;
}

unsigned char *ByteBuffer::getByteArray() const {
    return buffer;
}

void ByteBuffer::write(void *src, unsigned int size) {
    if (offset + size > bufferSize)
        std::cout << "[ByteBuffer]: write out of bound" << std::endl;
    memcpy(buffer + offset, src, size);
    offset += size;
}

unsigned int ByteBuffer::length() const {
    return bufferSize;
}
