/*
 * Copyright (c) 2025, Trey Shaffer <trey@trsh.dev>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include <LibWeb/Bindings/IIRFilterNodePrototype.h>
#include <LibWeb/Bindings/Intrinsics.h>
#include <LibWeb/WebAudio/AudioNode.h>
#include <LibWeb/WebAudio/BaseAudioContext.h>
#include <LibWeb/WebAudio/IIRFilterNode.h>

namespace Web::WebAudio {

GC_DEFINE_ALLOCATOR(IIRFilterNode);

IIRFilterNode::IIRFilterNode(JS::Realm& realm, GC::Ref<BaseAudioContext> context, Vector<double> feedforward, Vector<double> feedback)
    : AudioNode(realm, context)
    , m_feedforward(move(feedforward))
    , m_feedback(move(feedback))
{
}

IIRFilterNode::~IIRFilterNode() = default;

WebIDL::ExceptionOr<GC::Ref<IIRFilterNode>> IIRFilterNode::create(JS::Realm& realm, GC::Ref<BaseAudioContext> context, Vector<double> feedforward, Vector<double> feedback)
{
    return construct_impl(realm, context, move(feedforward), move(feedback));
}

// https://webaudio.github.io/web-audio-api/#dom-iirfilternode-iirfilternode
WebIDL::ExceptionOr<GC::Ref<IIRFilterNode>> IIRFilterNode::construct_impl(JS::Realm& realm, GC::Ref<BaseAudioContext> context, Vector<double> feedforward, Vector<double> feedback)
{
    // 1. If feedforward is an empty array or has more than 20 elements, throw a NotSupportedError
    if (feedforward.is_empty() || feedforward.size() > 20) {
        return WebIDL::NotSupportedError::create(realm, "feedforward array must have between 1 and 20 elements"_string);
    }

    // 2. If feedback is an empty array or has more than 20 elements, throw a NotSupportedError
    if (feedback.is_empty() || feedback.size() > 20) {
        return WebIDL::NotSupportedError::create(realm, "feedback array must have between 1 and 20 elements"_string);
    }

    // 3. If the first element of feedback is 0, throw an InvalidStateError
    if (feedback[0] == 0.0) {
        return WebIDL::InvalidStateError::create(realm, "First element of feedback array cannot be 0"_string);
    }

    // 4. Create the node
    auto node = realm.create<IIRFilterNode>(realm, context, move(feedforward), move(feedback));

    // FIXME: 5. Set tail-time to yes

    // FIXME: 6. Initialize the AudioNode

    // FIXME: 7. Configure the node with the filter coefficients

    return node;
}

void IIRFilterNode::initialize(JS::Realm& realm)
{
    Base::initialize(realm);
    WEB_SET_PROTOTYPE_FOR_INTERFACE(IIRFilterNode);
}

// https://webaudio.github.io/web-audio-api/#dom-iirfilternode-getfrequencyresponse
void IIRFilterNode::get_frequency_response(GC::Ref<WebIDL::Float32Array> frequency_hz, GC::Ref<WebIDL::Float32Array> mag_response, GC::Ref<WebIDL::Float32Array> phase_response)
{
    // 1. If frequencyHz, magResponse and phaseResponse are not all of the same length, throw an InvalidAccessError
    auto freq_length = frequency_hz->length();
    if (mag_response->length() != freq_length || phase_response->length() != freq_length) {
        // FIXME: Should throw InvalidAccessError
        return;
    }

    // 2. For each frequency in frequencyHz, compute the frequency response
    // FIXME: This is a stub implementation. The actual computation involves
    // evaluating the transfer function H(z) = B(z)/A(z) at each frequency
    // where B(z) is the feedforward polynomial and A(z) is the feedback polynomial
    
    // For now, just fill with dummy values (unity gain, zero phase)
    for (u32 i = 0; i < freq_length; ++i) {
        mag_response->data()[i] = 1.0f;
        phase_response->data()[i] = 0.0f;
    }
}

}