#ifndef GAME_ENGINE_HPP
#define GAME_ENGINE_HPP

#include "Core/Common.hpp"
#include "Core/Config.hpp"
#include "Core/Utility/Tool.hpp"

class GameEngine {
public:
    static GLFWwindow *window;
    static string window_name;
    static unsigned int window_width;
    static unsigned int window_height;

    // static 
    // explicit GameEngine(string w_name = "demo");
    // explicit GameEngine(unsigned int w_width, unsigned int w_height, string w_name = "demo");
    // void run();
// private:
    // void init();
    // void createWindow();
    // void processKeyboardInput();
};
// static void resizeWindowCallback(GLFWwindow* window, int width, int height);
// static void mouseMovecallback(GLFWwindow* window, double xpos, double ypos);
// static void scrollcallback(GLFWwindow* window, double xoffset, double yoffset);
#endif