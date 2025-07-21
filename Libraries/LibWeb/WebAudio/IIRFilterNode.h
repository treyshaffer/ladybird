/*
 * Copyright (c) 2025, Trey Shaffer <trey@trsh.dev>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#pragma once

#include <LibWeb/Bindings/IIRFilterNodePrototype.h>
#include <LibWeb/WebAudio/AudioNode.h>
#include <LibWeb/WebIDL/Buffers.h>

namespace Web::WebAudio {

// https://webaudio.github.io/web-audio-api/#IIRFilterNode
class IIRFilterNode final : public AudioNode {
    WEB_PLATFORM_OBJECT(IIRFilterNode, AudioNode);
    GC_DECLARE_ALLOCATOR(IIRFilterNode);

public:
    virtual ~IIRFilterNode() override;

    static WebIDL::ExceptionOr<GC::Ref<IIRFilterNode>> create(JS::Realm&, GC::Ref<BaseAudioContext>, Vector<double> feedforward, Vector<double> feedback);
    static WebIDL::ExceptionOr<GC::Ref<IIRFilterNode>> construct_impl(JS::Realm&, GC::Ref<BaseAudioContext>, Vector<double> feedforward, Vector<double> feedback);

    void get_frequency_response(GC::Ref<WebIDL::Float32Array> frequency_hz, GC::Ref<WebIDL::Float32Array> mag_response, GC::Ref<WebIDL::Float32Array> phase_response);

protected:
    IIRFilterNode(JS::Realm&, GC::Ref<BaseAudioContext>, Vector<double> feedforward, Vector<double> feedback);

    virtual void initialize(JS::Realm&) override;

private:
    Vector<double> m_feedforward;
    Vector<double> m_feedback;
};

}