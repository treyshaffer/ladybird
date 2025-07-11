/*
 * Copyright (c) 2025, Trey Shaffer <trey@trsh.dev>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#pragma once

#include <LibWeb/Bindings/ConvolverNodePrototype.h>
#include <LibWeb/WebAudio/AudioNode.h>

namespace Web::WebAudio {

// https://webaudio.github.io/web-audio-api/#ConvolverOptions
struct ConvolverOptions : AudioNodeOptions {
    GC::Ptr<AudioBuffer> buffer;
    bool disable_normalization { false };
};

// https://webaudio.github.io/web-audio-api/#ConvolverNode
class ConvolverNode : public AudioNode {
    WEB_PLATFORM_OBJECT(ConvolverNode, AudioNode);
    GC_DECLARE_ALLOCATOR(ConvolverNode);

public:
    virtual ~ConvolverNode() override;

    static WebIDL::ExceptionOr<GC::Ref<ConvolverNode>> create(JS::Realm&, GC::Ref<BaseAudioContext>, ConvolverOptions const& = {});
    static WebIDL::ExceptionOr<GC::Ref<ConvolverNode>> construct_impl(JS::Realm&, GC::Ref<BaseAudioContext>, ConvolverOptions const& = {});

    WebIDL::UnsignedLong number_of_inputs() override { return 1; }
    WebIDL::UnsignedLong number_of_outputs() override { return 1; }

    GC::Ptr<AudioBuffer> buffer() const { return m_buffer; }
    WebIDL::ExceptionOr<void> set_buffer(GC::Ptr<AudioBuffer>);

    bool normalize() const { return m_normalize; }
    void set_normalize(bool normalize) { m_normalize = normalize; }

protected:
    ConvolverNode(JS::Realm&, GC::Ref<BaseAudioContext>, ConvolverOptions const& = {});

    virtual void initialize(JS::Realm&) override;
    virtual void visit_edges(Cell::Visitor&) override;

private:
    GC::Ptr<AudioBuffer> m_buffer;
    bool m_normalize { true };
};

}