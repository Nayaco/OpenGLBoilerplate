#ifndef GAME_ENGINE_HPP
#define GAME_ENGINE_HPP

#include "Core/Common.hpp"
#include "Core/Config.hpp"
#include "Core/Context/Context.hpp"
#include "Core/Input/Input.hpp"
#include "Core/Scene/BaseScene.hpp"
#include "Core/Graphics/Shader/Shader.hpp"

class GameEngine {
public:
    static std::string  window_name;
    static unsigned int window_width;
    static unsigned int window_height;

    static BaseScene* scene;

    static void setname(std::string w_name = "demo");
    static void setsize(unsigned int w_width = DEFAULT_SCREEN_WIDTH, 
                        unsigned int w_height = DEFAULT_SCREEN_HEIGHT);
                        
    static void bindContext();
    static void bindScene(BaseScene* _scene);

    static void initialize();
    static void createContext();
    static void start_render();
};
#endif