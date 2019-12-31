//
// Created by Henry Little on 2019/12/29.
//

#ifndef SOLAR_FRAMEBUFFER_H
#define SOLAR_FRAMEBUFFER_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

enum FBOType{
    REFLECTION = 0,
    REFRACTION = 1
};

class FrameBuffer {
public:
    FrameBuffer(int width, int height, FBOType type);
    void bind();
    static void unbind(int windowWidth, int windowHeight);
    GLuint getColorBuffer();
    GLuint getDepthBuffer();
private:
    GLuint ID;
    GLuint colorAttachment;
    GLuint depthAttachment;
    int width;
    int height;

    static GLuint createColorAttachment(int mWidth, int mHeight);

    static GLuint createDepthAttachment(int mWidth, int mHeight);

    static GLuint createDepthBufferAttachment(int mWidth, int mHeight);
};


#endif //SOLAR_FRAMEBUFFER_H
