/**
 * main.cpp - Execution begins here.
 * ------------------------------------------------------------------------
 *
 * Copyright (c) 2024-present Ajay Sreedhar
 * 
 * Licensed under the MIT License.
 * Please see the LICENSE file located in the root directory.
 *
 * ========================================================================
 */

#include <cstdlib>
#include <thread>
#include "platform/logger.hpp"
#include "platform/filesystem.hpp"
#include "input/pipewire_client.hpp"
#include "ui/except.hpp"
#include "ui/sprite_material.hpp"
#include "ui/renderer.hpp"
#include "ui/display_context.hpp"

struct audio_payload {
    bool chFlag[2];
    bmx::SpriteMaterial* lt_woofer;
    bmx::SpriteMaterial* rt_woofer;
};

void onAudioInput(int channel, int peak, void* payload) {
    auto pl = reinterpret_cast<struct audio_payload*>(payload);

    bmx::SpriteMaterial* target_sprite = channel == 0 ? pl->lt_woofer : pl->rt_woofer;

    if (peak >= 25) {
        target_sprite->setScissor(270, 0);
        pl->chFlag[channel] = true;
    }
}

int main(int argc, char** argv) {
    bool is_running = true;
    bool should_draw = true;

    std::thread::id main_thread_id = std::this_thread::get_id();

    bmx::DisplayContext::initialise();
    bmx::PipewireClient::initialise(argc, argv);
    bmx::Logger::info("Welcome to Boombox!");

    bmx::Renderer* main_renderer = nullptr;
    auto audio_client = bmx::PipewireClient::factory();

    try {
        main_renderer = bmx::DisplayContext::createRenderer();

    } catch (bmx::UIError& error) {
        bmx::Logger::fatal(error.what(), error.getCode());
        return EXIT_FAILURE;
    }

    bmx::SpriteMaterial* window_bg = main_renderer->loadSprite(bmx::Filesystem::resource("skins/default", "background-main.png"));
    bmx::SpriteMaterial* lt_woofer = main_renderer->loadSprite(bmx::Filesystem::resource("skins/default", "sprite-map-main.png"));
    bmx::SpriteMaterial* rt_woofer = lt_woofer->clone();

    struct audio_payload event_payload {
        .chFlag = {false, false},
        .lt_woofer = lt_woofer,
        .rt_woofer = rt_woofer
    };

    bmx::AudioEvent audio_event {
        .listener = onAudioInput,
        .payload = &event_payload
    };

    audio_client->onCapture(&audio_event);

    lt_woofer->setScissor(0, 0, 270, 270);
    lt_woofer->setAttachment(100, 100, 270, 270);

    rt_woofer->setScissor(0, 0, 270, 270);
    rt_woofer->setAttachment(window_bg->getWidth() - (270 + 100), 100, 270, 270);

    main_renderer->draw(window_bg);
    main_renderer->draw(lt_woofer);
    main_renderer->draw(rt_woofer);

    main_renderer->commit();

    auto audio_thread = new std::thread(&bmx::PipewireClient::capture, audio_client);
    audio_thread->detach();

    while (is_running) {
        bmx::DisplayContext::UIEvent ui_event = bmx::DisplayContext::pollEvent();

        switch (ui_event.kind){
            case bmx::DisplayContext::UIEvent::WINDOW_CLOSE:
            case bmx::DisplayContext::UIEvent::PROCESS_QUIT:
            case bmx::DisplayContext::UIEvent::KEY_PRESS_Q:
                is_running = false;
                break;

            case bmx::DisplayContext::UIEvent::KEY_PRESS_S:
                lt_woofer->setScissor(270, 0);
                rt_woofer->setScissor(270, 0);
                break;

            case bmx::DisplayContext::UIEvent::KEY_PRESS_W:
                lt_woofer->setScissor(0, 0);
                rt_woofer->setScissor(0, 0);
                break;

            default:
                break;
        }

        if (should_draw) {
            lt_woofer->setScissor(0, 0);
            rt_woofer->setScissor(0, 0);

            main_renderer->clear();

            main_renderer->draw(window_bg);
            main_renderer->draw(lt_woofer);
            main_renderer->draw(rt_woofer);
            main_renderer->commit();

            should_draw = false;
            continue;
        }

        should_draw = true;

        for (int i = 0; i < 2; i++) {
            should_draw = should_draw && event_payload.chFlag[i];
            event_payload.chFlag[i] = false;
        }

        if (should_draw) {
            main_renderer->clear();

            main_renderer->draw(window_bg);
            main_renderer->draw(lt_woofer);
            main_renderer->draw(rt_woofer);
            main_renderer->commit();
        }
    }

    audio_client->halt();

    /* Wait for the pipewire main loop to quit. */
    while (audio_client->isRunning()) {
        sleep(1);
    }

    delete (rt_woofer);
    delete (lt_woofer);
    delete (window_bg);
    delete (audio_client);

    bmx::DisplayContext::shutdown();
    bmx::PipewireClient::shutdown();

    delete audio_thread;

    bmx::Logger::info("Bye!");

    return EXIT_SUCCESS;
}
