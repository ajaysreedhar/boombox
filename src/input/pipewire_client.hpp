/**
 * pipewire_client.hpp - Pipewire client implementation.
 * ------------------------------------------------------------------------
 *
 * Copyright (c) 2024-present Ajay Sreedhar
 * 
 * Licensed under the MIT License.
 * Please see the LICENSE file located in the root directory.
 *
 * ========================================================================
 */

#ifndef BMX_INPUT_PIPEWIRE_CLIENT_H
#define BMX_INPUT_PIPEWIRE_CLIENT_H

#include <pipewire/pipewire.h>
#include <spa/param/audio/format-utils.h>
#include "audio_client.hpp"

namespace bmx {

struct input_bundle {
    struct pw_main_loop*    loop;
    struct pw_stream*       stream;
    struct spa_audio_info   format;
    bool*                   running;
    bmx::AudioEvent*        event;
};

typedef struct input_bundle InputBundle;

/**
 * @brief Client capturing audio from Pipewire interface.
 */
class PipewireClient: public bmx::AudioClient {

private: /* ===-=== Private members ===-=== */
    static bool s_isInitialised;

    bool m_isRunning = false;

    uint8_t m_buffer[1024];
    
    struct pw_main_loop*    m_pwLoop;
    struct pw_properties*   m_pwProps;
    struct pw_stream*       m_pwStream;
    struct pw_stream_events m_pwEvents {PW_VERSION_STREAM_EVENTS};
    
    struct spa_pod_builder  m_podBuilder;

    bmx::InputBundle        m_payload;

    explicit PipewireClient();

    static void onStreamChangedCb(void*, uint32_t, const struct spa_pod*);
    static void onProcessHolderCb(void*);

public: /* ===-=== Public members ===-=== */
    static void initialise(int, char**);
    static void shutdown();
    static PipewireClient* factory();

    void capture();
    void halt();
    void onCapture(AudioEvent*);
    bool isRunning();

    ~PipewireClient();
};

} // namespace bmx

#endif // BMX_INPUT_PIPEWIRE_CLIENT_H