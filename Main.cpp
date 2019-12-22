#define STB_IMAGE_IMPLEMENTATION

#include "Core/GameEngine.hpp"
#include "Components/Scenes/Demo/DemoScene.hpp"
#include "Core/ExceptionHandle/ErrLog.hpp"

int main(int argc, char const *argv[])
{
    try {
    DemoScene demo_scene;
    demo_scene.setViewport(800, 600);
    
    logger.warning("1");GameEngine::setname();
    logger.warning("2");GameEngine::setsize();
    logger.warning("3");GameEngine::createWindow();
    logger.warning("4");GameEngine::bindScene(&demo_scene);
    logger.warning("5");GameEngine::initialize();
    logger.warning("6");GameEngine::start_render();
    } catch (string e) {
        logger.error(e);
    }
    return 0;
}
