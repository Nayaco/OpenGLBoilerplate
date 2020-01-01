//
// Created by Henry Little on 2019/9/15.
//

#ifndef RENDERENGINE_BYTEBUFFER_H
#define RENDERENGINE_BYTEBUFFER_H


class ByteBuffer {
public:
    explicit ByteBuffer(unsigned int byteCount);

    void write(void *src, unsigned int size);

    unsigned char *getByteArray() const;

    unsigned int length() const;

private:
    unsigned int offset = 0;
    unsigned int bufferSize;
    unsigned char *buffer;
};


#endif //RENDERENGINE_BYTEBUFFER_H
