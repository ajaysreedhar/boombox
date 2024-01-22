#include <cstdlib>
#include "platform/logger.hpp"
#include "platform/filesystem.hpp"
#include "ui/except.hpp"
#include "ui/sprite_material.hpp"
#include "ui/renderer.hpp"
#include "ui/display_context.hpp"

int main(int argc, char** argv) {
    bool is_running = true;

    bmx::DisplayContext::initialise();
    bmx::Logger::info("Welcome to Boombox!");

    bmx::Renderer* main_renderer = nullptr;

    try {
        main_renderer = bmx::DisplayContext::createRenderer();

    } catch (bmx::UIError& error) {
        bmx::Logger::fatal(error.what(), error.getCode());
        return EXIT_FAILURE;
    }

    bmx::SpriteMaterial* window_bg = main_renderer->loadSprite(bmx::Filesystem::resource("skins/default", "background-main.png"));
    bmx::SpriteMaterial* lt_woofer = main_renderer->loadSprite(bmx::Filesystem::resource("skins/default", "sprite-map-main.png"));
    bmx::SpriteMaterial* rt_woofer = lt_woofer->clone();

    lt_woofer->setScissor(0, 0, 270, 270);
    lt_woofer->setAttachment(100, 100, 270, 270);

    rt_woofer->setScissor(0, 0, 270, 270);
    rt_woofer->setAttachment(window_bg->getWidth() - (270 + 100), 100, 270, 270);

    main_renderer->draw(window_bg);
    main_renderer->draw(lt_woofer);
    main_renderer->draw(rt_woofer);

    main_renderer->commit();

    while (is_running) {
        bmx::DisplayContext::UIEvent ui_event = bmx::DisplayContext::pollEvent();

        switch (ui_event.kind){
            case bmx::DisplayContext::UIEvent::WINDOW_CLOSE:
            case bmx::DisplayContext::UIEvent::PROCESS_QUIT:
            case bmx::DisplayContext::UIEvent::KEY_PRESS_Q:
                is_running = false;
                break;

            default:
                break;
        }
    }

    delete (rt_woofer);
    delete (lt_woofer);
    delete (window_bg);

    bmx::DisplayContext::shutdown();
    bmx::Logger::info("Bye!");

    return EXIT_SUCCESS;
}
