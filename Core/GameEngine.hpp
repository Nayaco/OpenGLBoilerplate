#ifndef GAME_ENGINE_HPP
#define GAME_ENGINE_HPP

#include "Core/Common.hpp"
#include "Core/Config.hpp"
#include "Core/Input/Input.hpp"
#include "Core/Scene/BaseScene.hpp"
#include "Core/Graphics/Shader/Shader.hpp"

#include "Core/Utility/Tool.hpp"

class GameEngine {
public:
    static GLFWwindow  *window;
    static std::string  window_name;
    static unsigned int window_width;
    static unsigned int window_height;

    static float game_time;
    static float delta_time;
    static float current_frame;
    static float last_frame;

    static BaseScene* scene;
    // static

    static void setname(std::string w_name = "demo");
    static void setsize(unsigned int w_width = DEFAULT_SCREEN_WIDTH, 
                        unsigned int w_height = DEFAULT_SCREEN_HEIGHT);
    
    static void bindScene(BaseScene* _scene);

    static void initialize();
    static void createWindow();
    static void start_render();
    
    static void handleDeltaFrame();
    static void resizeWindowCallback(GLFWwindow* window, int width, int height);
};
#endif