#ifndef INPUT_HPP
#define INPUT_HPP

#include "Core/Common.hpp"

class Input {
public:
    struct MouseClick {
        glm::vec2 lefttop; 
        glm::vec2 rightbottom;
        std::function<void()> *callback;
    };
    static std::list<std::function<void(double)>*> scrollCallbacks;
    static std::list<std::function<void(double, double)>*> mousemoveCallbacks;
    static std::list<MouseClick> clickCallbacks;
    static std::function<void(double)> *onClick;

    static void mouseMovecallback(GLFWwindow* window, double xpos, double ypos);
    static void scrollcallback(GLFWwindow* window, double xoffset, double yoffset);
};


#endif