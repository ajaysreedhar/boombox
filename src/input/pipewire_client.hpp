#ifndef BMX_INPUT_PIPEWIRE_CLIENT_H
#define BMX_INPUT_PIPEWIRE_CLIENT_H

#include <pipewire/pipewire.h>
#include <spa/param/audio/format-utils.h>

namespace bmx {

/**
 * @brief Client capturing audio from Pipewire interface.
 */
class PipewireClient {

private: /* ===-=== Private members ===-=== */
    static bool s_isInitialised;

    uint8_t m_buffer[1024];
    
    struct pw_main_loop*    m_pwLoop;
    struct pw_properties*   m_pwProps;
    struct pw_stream*       m_pwStream;
    
    struct spa_pod_builder  m_podBuilder;

    explicit PipewireClient();

public: /* ===-=== Public members ===-=== */
    static void initialise(int, char**);
    static void shutdown();
    static PipewireClient* factory();

    void capture();

    ~PipewireClient();
};

} // namespace bmx

#endif // BMX_INPUT_PIPEWIRE_CLIENT_H