/*
 * Copyright (c) 2025, Trey Shaffer <trey@trsh.dev>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#pragma once

#include <LibWeb/Bindings/WaveShaperNodePrototype.h>
#include <LibWeb/WebAudio/AudioNode.h>
#include <LibWeb/WebIDL/Buffers.h>

namespace Web::WebAudio {

// https://webaudio.github.io/web-audio-api/#WaveShaperNode
class WaveShaperNode final : public AudioNode {
    WEB_PLATFORM_OBJECT(WaveShaperNode, AudioNode);
    GC_DECLARE_ALLOCATOR(WaveShaperNode);

public:
    virtual ~WaveShaperNode() override;

    static WebIDL::ExceptionOr<GC::Ref<WaveShaperNode>> create(JS::Realm&, GC::Ref<BaseAudioContext>, WaveShaperOptions const& = {});
    static WebIDL::ExceptionOr<GC::Ref<WaveShaperNode>> construct_impl(JS::Realm&, GC::Ref<BaseAudioContext>, WaveShaperOptions const& = {});

    GC::Ptr<WebIDL::Float32Array> curve() const { return m_curve; }
    void set_curve(GC::Ptr<WebIDL::Float32Array>);
    
    Bindings::OverSampleType oversample() const { return m_oversample; }
    void set_oversample(Bindings::OverSampleType oversample) { m_oversample = oversample; }

protected:
    WaveShaperNode(JS::Realm&, GC::Ref<BaseAudioContext>, WaveShaperOptions const& = {});

    virtual void initialize(JS::Realm&) override;
    virtual void visit_edges(Cell::Visitor&) override;

private:
    GC::Ptr<WebIDL::Float32Array> m_curve;
    Bindings::OverSampleType m_oversample { Bindings::OverSampleType::None };
};

}