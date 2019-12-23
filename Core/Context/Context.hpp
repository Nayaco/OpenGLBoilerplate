#ifndef CONTEXT_HPP
#define CONTEXT_HPP

#include "Core/Common.hpp"

class Context {
public:
    static GLFWwindow  *window;
    static std::string  window_name;
    static unsigned int window_width;
    static unsigned int window_height;
    
    static void create(std::string w_name, unsigned int w_width, unsigned int w_height, 
                        unsigned int gl_major, unsigned int gl_minor, unsigned int gl_sample);
    static GLFWwindow* getWindow();
    static void destroy();
    static void updateWindow(unsigned int w_width, unsigned int w_height);
};

#endif