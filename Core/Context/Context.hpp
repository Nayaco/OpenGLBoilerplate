#ifndef CONTEXT_HPP
#define CONTEXT_HPP

#include "Core/Common.hpp"

class Context {
public:
    static GLFWwindow  *window;
    static std::string  window_name;
    static unsigned int window_width;
    static unsigned int window_height;

    static float game_time;
    static float delta_time;
    static float current_frame;
    static float last_frame;
    
    static GLFWwindow* getWindow();
    static void create(std::string w_name, unsigned int w_width, unsigned int w_height, 
                        unsigned int gl_major, unsigned int gl_minor, unsigned int gl_sample);
    static void close();
    static void destroy();
    static void update();
    static bool shouldClose();
    static void swapbuffer();
    static void updateWindow(unsigned int w_width, unsigned int w_height);
    static void handleDeltaFrame();
};

#endif