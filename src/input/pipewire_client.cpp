/**
 * pipewire_client.cpp - Pipewire client implementation.
 * ------------------------------------------------------------------------
 *
 * Copyright (c) 2024-present Ajay Sreedhar
 * 
 * Licensed under the MIT License.
 * Please see the LICENSE file located in the root directory.
 *
 * ========================================================================
 */

#include <cmath>
#include <thread>
#include <csignal>
#include "platform/logger.hpp"
#include "except.hpp"
#include "pipewire_client.hpp"

bool bmx::PipewireClient::s_isInitialised = false;

void bmx::PipewireClient::onStreamChangedCb(void* bundle, uint32_t id, const struct spa_pod* pod_param) {
    auto payload = reinterpret_cast<bmx::InputBundle*>(bundle);

    if (pod_param == nullptr || id != SPA_PARAM_Format) {
        return void();
    }

    if (spa_format_parse(pod_param, &payload->format.media_type, &payload->format.media_subtype) < 0) {
        return void();
    }

    if (payload->format.media_type != SPA_MEDIA_TYPE_audio ||
        payload->format.media_subtype != SPA_MEDIA_SUBTYPE_raw) {
        return void();
    }

    spa_format_audio_raw_parse(pod_param, &payload->format.info.raw);

#if defined(BMX_MODE_DEBUG) && BMX_MODE_DEBUG == 1
    bmx::Logger::info("Capturing rate:", payload->format.info.raw.rate, ", Channels:", payload->format.info.raw.channels);
#endif // BMX_MODE_DEBUG
}

void bmx::PipewireClient::onProcessHolderCb(void* bundle) {
    auto payload = reinterpret_cast<bmx::InputBundle*>(bundle);

    struct pw_buffer *b;
    struct spa_buffer *buf;
    float* samples, max;

    uint32_t c, n, n_channels, n_samples, peak;

    if ((b = pw_stream_dequeue_buffer(payload->stream)) == nullptr) {
            pw_log_warn("out of buffers: %m");
            return void();
    }

    buf = b->buffer;
    if (buf->datas[0].data == nullptr) {
        return void();
    }

    samples = (float*) buf->datas[0].data;

    n_channels = payload->format.info.raw.channels;
    n_samples = buf->datas[0].chunk->size / sizeof(float);

    int peak_1, peak_2;

    for (c = 0; c < n_channels; c++) {
        max = 0.0f;
        for (n = c; n < n_samples; n += n_channels) {
            max = fmaxf(max, fabsf(samples[n]));
        }

        peak = SPA_CLAMP(max * 30, 0, 40);
    }

    pw_stream_queue_buffer(payload->stream, b);

    (*payload->event->listener)(payload->event->payload);
}

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
    const struct spa_pod* pod_params[1];
    struct spa_audio_info_raw audio_info {.format = SPA_AUDIO_FORMAT_F32};

    m_podBuilder = SPA_POD_BUILDER_INIT(m_buffer, sizeof(m_buffer));
    
    m_pwLoop = m_payload.loop = pw_main_loop_new(nullptr);
    m_pwProps = pw_properties_new(PW_KEY_MEDIA_TYPE, "Audio",
        PW_KEY_MEDIA_CATEGORY, "Capture",
        PW_KEY_MEDIA_ROLE, "Music", nullptr);

    m_pwEvents.param_changed = bmx::PipewireClient::onStreamChangedCb;
    m_pwEvents.process = onProcessHolderCb;

    m_payload.running = &m_isRunning;
    m_pwStream = m_payload.stream = pw_stream_new_simple(pw_main_loop_get_loop(m_pwLoop), "boombox", m_pwProps, &m_pwEvents, &m_payload);

    pod_params[0] = spa_format_audio_raw_build(&m_podBuilder, SPA_PARAM_EnumFormat, &audio_info);

    pw_stream_connect(m_pwStream,
        PW_DIRECTION_INPUT,
        PW_ID_ANY,
        (pw_stream_flags)(PW_STREAM_FLAG_AUTOCONNECT |
        PW_STREAM_FLAG_MAP_BUFFERS |
        PW_STREAM_FLAG_RT_PROCESS),
        pod_params, 1);
}

bmx::PipewireClient::~PipewireClient() {
    pw_main_loop_destroy(m_pwLoop);

#if defined(BMX_MODE_DEBUG) && BMX_MODE_DEBUG == 1
    bmx::Logger::debug("Pipewire client destroyed.");
#endif // BMX_MODE_DEBUG
}

void bmx::PipewireClient::capture() {
    m_isRunning = true;

    pw_main_loop_run(m_pwLoop);
    pw_stream_destroy(m_pwStream);

    m_isRunning = false;

#if defined(BMX_MODE_DEBUG) && BMX_MODE_DEBUG == 1
    bmx::Logger::debug("Pipewire capture aborted.");
#endif // BMX_MODE_DEBUG

    return void();
}

void bmx::PipewireClient::halt() {
    pw_main_loop_quit(m_pwLoop);
}

void bmx::PipewireClient::onCapture(AudioEvent* event) {
    m_payload.event = event;
}

bool bmx::PipewireClient::isRunning() {
    return m_isRunning;
}
