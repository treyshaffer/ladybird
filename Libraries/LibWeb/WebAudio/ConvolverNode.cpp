/*
 * Copyright (c) 2025, Trey Shaffer <trey@trsh.dev>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include <LibWeb/WebAudio/AudioBuffer.h>
#include <LibWeb/WebAudio/AudioNode.h>
#include <LibWeb/WebAudio/BaseAudioContext.h>
#include <LibWeb/WebAudio/ConvolverNode.h>
#include <LibWeb/Bindings/ConvolverNodePrototype.h>
#include <LibWeb/Bindings/Intrinsics.h>

namespace Web::WebAudio {

GC_DEFINE_ALLOCATOR(ConvolverNode);

ConvolverNode::~ConvolverNode() = default;

WebIDL::ExceptionOr<GC::Ref<ConvolverNode>> ConvolverNode::create(JS::Realm& realm, GC::Ref<BaseAudioContext> context, ConvolverOptions const& options)
{
    return construct_impl(realm, context, options);
}

// https://webaudio.github.io/web-audio-api/#dom-convolvernode-convolvernode
WebIDL::ExceptionOr<GC::Ref<ConvolverNode>> ConvolverNode::construct_impl(JS::Realm& realm, GC::Ref<BaseAudioContext> context, ConvolverOptions const& options)
{
    // 1. Create the node and allocate memory
    auto node = realm.create<ConvolverNode>(realm, context, options);

    // 2. Default options for channel count and interpretation
    // https://webaudio.github.io/web-audio-api/#ConvolverNode
    AudioNodeDefaultOptions default_options;
    default_options.channel_count_mode = Bindings::ChannelCountMode::ClampedMax;
    default_options.channel_interpretation = Bindings::ChannelInterpretation::Speakers;
    default_options.channel_count = 2;
    // FIXME: Set tail-time to yes

    // 3. Initialize the AudioNode options
    TRY(node->initialize_audio_node_options(options, default_options));

    // 4. If options.buffer is specified
    if (options.buffer) {
        // Check that the buffer sample rate matches the context sample rate
        if (options.buffer->sample_rate() != context->sample_rate()) {
            return WebIDL::NotSupportedError::create(realm, "Buffer sample rate does not match context sample rate"_string);
        }
        node->m_buffer = options.buffer;
    }

    // 5. Set normalize based on disableNormalization option
    node->m_normalize = !options.disable_normalization;

    return node;
}

ConvolverNode::ConvolverNode(JS::Realm& realm, GC::Ref<BaseAudioContext> context, ConvolverOptions const&)
    : AudioNode(realm, context)
{
}

void ConvolverNode::initialize(JS::Realm& realm)
{
    WEB_SET_PROTOTYPE_FOR_INTERFACE(ConvolverNode);
    Base::initialize(realm);
}

void ConvolverNode::visit_edges(Cell::Visitor& visitor)
{
    Base::visit_edges(visitor);
    visitor.visit(m_buffer);
}

// https://webaudio.github.io/web-audio-api/#dom-convolvernode-buffer
WebIDL::ExceptionOr<void> ConvolverNode::set_buffer(GC::Ptr<AudioBuffer> buffer)
{
    // 1. If the buffer number of channels is not 1, 2, 4, or the sampleRate of the buffer is not the same as the sampleRate of the context, 
    //    a NotSupportedError MUST be thrown.
    if (buffer) {
        auto channels = buffer->number_of_channels();
        if (channels != 1 && channels != 2 && channels != 4) {
            return WebIDL::NotSupportedError::create(realm(), "Buffer must have 1, 2, or 4 channels"_string);
        }
        if (buffer->sample_rate() != context()->sample_rate()) {
            return WebIDL::NotSupportedError::create(realm(), "Buffer sample rate does not match context sample rate"_string);
        }
    }

    // 2. Assign buffer to the buffer attribute.
    m_buffer = buffer;

    // FIXME: 3. Acquire the contents of buffer

    return {};
}

}