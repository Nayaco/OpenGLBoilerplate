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

    enum class Keys {
        KEY_W,
        KEY_A,
        KEY_S,
        KEY_D,
        
        KEY_SPACE,
        KEY_ESC,
        KEY_ENTER,
        KEY_Q,
        KEY_P,

        KEY_UP,
        KEY_DOWN,
        KEY_LEFT,
        KEY_RIGHT,
    };

    static std::list<std::function<void(float)>* > scrollCallbacks;
    static std::list<std::function<void(float, float)>* > mousemoveCallbacks;
    static std::list<MouseClick> clickCallbacks;
    static std::function<void()> *onClick;
    static std::map<Keys, std::list<std::function<void(float, float)>* > > keyCallbacks;


    static void mouseMoveCallback(GLFWwindow* window, double xpos, double ypos);
    static void scrollCallback(GLFWwindow* window, double xoffset, double yoffset);
    static void processKeyInput(GLFWwindow* window);
};


#endif