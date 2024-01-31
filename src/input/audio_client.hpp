/**
 * audio_client.hpp - Audio client abstract class.
 * ------------------------------------------------------------------------
 *
 * Copyright (c) 2024-present Ajay Sreedhar
 * 
 * Licensed under the MIT License.
 * Please see the LICENSE file located in the root directory.
 *
 * ========================================================================
 */

#ifndef BMX_INPUT_AUDIO_CLIENT_H
#define BMX_INPUT_AUDIO_CLIENT_H

namespace bmx {

struct audio_event {
    void (*listener)(void *);
    void* payload;
};

typedef struct audio_event AudioEvent;

class AudioClient {

public:
    virtual void capture() = 0;
    virtual void halt() = 0;
    virtual bool isRunning() = 0;
};

} // namespace bmx

#endif // BMX_INPUT_AUDIO_CLIENT_H
