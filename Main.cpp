#define STB_IMAGE_IMPLEMENTATION

#include "Core/GameEngine.hpp"
#include "Components/Scenes/Demo/DemoScene.hpp"
#include "Components/Scenes/GameScene/GameScene.hpp"
#include "Core/ExceptionHandle/ErrLog.hpp"

int main(int argc, char const *argv[])
{
    try {
        GameScene game_scene;
        logger.warning("1");GameEngine::setname();
        logger.warning("2");GameEngine::setsize();
        logger.warning("3");GameEngine::createContext();
        logger.warning("4");GameEngine::bindScene(&game_scene);
        logger.warning("5");GameEngine::initialize();
        logger.warning("6");GameEngine::start_render();
    } catch (char const *e) {
        logger.error(string(e));
    } catch (string e) {
        logger.error(e);
    }
    return 0;
}
