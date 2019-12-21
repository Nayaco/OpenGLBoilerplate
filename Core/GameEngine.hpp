#ifndef GAME_ENGINE_HPP
#define GAME_ENGINE_HPP

#include "Core/Common.hpp"
#include "Core/Config.hpp"
#include "Core/Input/Input.hpp"
#include "Core/Utility/Tool.hpp"
class GameEngine {
public:
    static GLFWwindow *window;
    static std::string window_name;
    static unsigned int window_width;
    static unsigned int window_height;
    
    // explicit GameEngine(string w_name = "demo");
    // explicit GameEngine(unsigned int w_width, unsigned int w_height, string w_name = "demo");
    // void run();
// private:
    static void setname(std::string w_name = "demo");
    static void setsize(unsigned int w_width, unsigned int w_height);
    static void initialize();
    static void createWindow();
    static void resizeWindowCallback(GLFWwindow* window, int width, int height);
};
#endif