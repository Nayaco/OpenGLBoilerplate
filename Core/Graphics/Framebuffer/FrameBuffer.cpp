//
// Created by Henry Little on 2019/12/29.
//

#include <iostream>
#include "FrameBuffer.h"

FrameBuffer::FrameBuffer(int width, int height, FBOType type) :
        width(width), height(height) {
    ID = 0;
    // generate the frame buffer
    glGenFramebuffers(1, &ID);
    /* set attachments */
    // bind the FBO
    glBindFramebuffer(GL_FRAMEBUFFER, ID);
    glDrawBuffer(GL_COLOR_ATTACHMENT0);
    colorAttachment = createColorAttachment(width, height);

    switch (type) {
        case REFLECTION:
            depthAttachment = 0;
            depthAttachment = createDepthBufferAttachment(width, height);
            break;
        case REFRACTION:
            depthAttachment = 0;
            depthAttachment = createDepthAttachment(width, height);
            break;
    }
    auto fboStatus = glCheckFramebufferStatus(GL_FRAMEBUFFER);
    if (fboStatus != GL_FRAMEBUFFER_COMPLETE) {
        std::cout << "Framebuffer not complete: " << fboStatus << std::endl;
    } else {
        // std::cout << "Framebuffer Created: " << ID << " colorAttach: " << colorAttachment << " depthAttach: "
        //           << depthAttachment << std::endl;
    }

    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

GLuint FrameBuffer::createColorAttachment(int mWidth, int mHeight) {
    // gen the texture
    GLuint texture = 0;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, mWidth, mHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, texture, 0);
    return texture;
}

GLuint FrameBuffer::createDepthAttachment(int mWidth, int mHeight) {
    GLuint texture = 0;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT24, mWidth, mHeight,
                 0, GL_DEPTH_COMPONENT, GL_UNSIGNED_BYTE, nullptr);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, texture, 0);
    return texture;
}

void FrameBuffer::bind() {
    glBindTexture(GL_TEXTURE_2D, 0);
    glBindFramebuffer(GL_FRAMEBUFFER, ID);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glViewport(0, 0, width, height);
}

void FrameBuffer::unbind(int windowWidth, int windowHeight) {
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glViewport(0, 0, windowWidth, windowHeight);
//    glDrawBuffer(GL_BACK);
}

GLuint FrameBuffer::createDepthBufferAttachment(int mWidth, int mHeight) {
    GLuint depthBuffer = 0;
    glGenRenderbuffers(1, &depthBuffer);
    glBindRenderbuffer(GL_RENDERBUFFER, depthBuffer);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT24, mWidth, mHeight);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, depthBuffer);
    return depthBuffer;
}

GLuint FrameBuffer::getColorBuffer() {
    return colorAttachment;
}

GLuint FrameBuffer::getDepthBuffer() {
    return depthAttachment;
}




