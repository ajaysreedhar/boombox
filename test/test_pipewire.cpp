#include <thread>
#include <iostream>

#include "platform/logger.hpp"
#include "input/pipewire_client.hpp"

int main (int argc, char** argv) {
    std::thread::id thread_id = std::this_thread::get_id();
    bmx::Logger::debug("Main thread ", thread_id);

    bmx::PipewireClient::initialise(argc, argv);
    bmx::Logger::info("Welcome to Pipewire Client Test!");

    auto audio_client = bmx::PipewireClient::factory();
    
    auto audio_thread = new std::thread(&bmx::PipewireClient::capture, audio_client);
    audio_thread->detach();

    bmx::Logger::info("Press Enter to exit...");
    std::cin.get();

    audio_client->halt();

    while (audio_client->isRunning()) {
        sleep(1);
    }

    delete (audio_thread);
    delete (audio_client);

    bmx::PipewireClient::shutdown();

    return 0;
}
