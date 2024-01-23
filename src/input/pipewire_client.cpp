#include "except.hpp"
#include "pipewire_client.hpp"

bool bmx::PipewireClient::s_isInitialised = false;

void bmx::PipewireClient::initialise(int argc, char** argv) {
    pw_init(&argc, &argv);
    s_isInitialised = true;
}

void bmx::PipewireClient::shutdown() {
    if (s_isInitialised == true) {
        pw_deinit();
        s_isInitialised = false;
    }
}

bmx::PipewireClient* bmx::PipewireClient::factory() {
    if (s_isInitialised == false) {
        throw bmx::InputError("Pipewire client is not initialised.", bmx::InputError::E_TYPE_GENERAL);
    }

    return new PipewireClient();
}

bmx::PipewireClient::PipewireClient() {
    m_podBuilder = SPA_POD_BUILDER_INIT(m_buffer, sizeof(m_buffer));
    
    m_pwLoop = pw_main_loop_new(nullptr);
    m_pwProps = pw_properties_new(PW_KEY_MEDIA_TYPE, "Audio",
        PW_KEY_MEDIA_CATEGORY, "Capture",
        PW_KEY_MEDIA_ROLE, "Music", nullptr);

    // m_pwStream = pw_stream_new_simple(pw_main_loop_get_loop(m_pwLoop), "boombox", m_pwProps, );
}

bmx::PipewireClient::~PipewireClient() {
    pw_stream_destroy(m_pwStream);
    pw_main_loop_destroy(m_pwLoop);
}

void bmx::PipewireClient::capture() {
    pw_main_loop_run(m_pwLoop);
}
