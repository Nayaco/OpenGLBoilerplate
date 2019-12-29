#ifndef INPUT_HPP
#define INPUT_HPP

#include "Core/Common.hpp"
#include "Core/Context/Context.hpp"
class Input {
public:
    struct MouseClick {
        glm::vec2 lefttop; 
        glm::vec2 rightbottom;
        std::function<void()> *callback;
    };

    enum Keys {
        KEY_W = GLFW_KEY_W,
        KEY_A = GLFW_KEY_A,
        KEY_S = GLFW_KEY_S,
        KEY_D = GLFW_KEY_D,
        KEY_F = GLFW_KEY_F,
        
        KEY_SPACE = GLFW_KEY_SPACE,
        KEY_ESC   = GLFW_KEY_ESCAPE,
        KEY_ENTER = GLFW_KEY_ENTER,
        KEY_Q     = GLFW_KEY_Q,
        KEY_P     = GLFW_KEY_P,

        KEY_UP    = GLFW_KEY_UP,
        KEY_DOWN  = GLFW_KEY_DOWN,
        KEY_LEFT  = GLFW_KEY_LEFT,
        KEY_RIGHT = GLFW_KEY_RIGHT,
    };

    static std::list<std::function<void(float)>* > scrollCallbacks;
    static std::list<std::function<void(float, float)>* > mousemoveCallbacks;
    static std::list<MouseClick> clickCallbacks;
    static std::function<void()> *onClick;
    static std::map<Keys, std::list<std::function<void()>* > > keyCallbacks;

    static void bind();
    
    static void bindMousemoveCallback(std::function<void(float, float)>* func);
    static void bindScrollCallback(std::function<void(float)>* func);
    static void bindKeydownCallback(Keys key, std::function<void()>* func);

    static void resizeWindowCallback(GLFWwindow* window, int width, int height);
    static void mouseMoveCallback(GLFWwindow* window, double xpos, double ypos);
    static void scrollCallback(GLFWwindow* window, double xoffset, double yoffset);
    static void processKeyInput();
};


#endif