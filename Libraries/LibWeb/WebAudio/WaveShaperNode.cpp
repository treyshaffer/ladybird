/*
 * Copyright (c) 2025, Trey Shaffer <trey@trsh.dev>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include <LibWeb/Bindings/Intrinsics.h>
#include <LibWeb/Bindings/WaveShaperNodePrototype.h>
#include <LibWeb/WebAudio/AudioNode.h>
#include <LibWeb/WebAudio/BaseAudioContext.h>
#include <LibWeb/WebAudio/WaveShaperNode.h>

namespace Web::WebAudio {

GC_DEFINE_ALLOCATOR(WaveShaperNode);

WaveShaperNode::WaveShaperNode(JS::Realm& realm, GC::Ref<BaseAudioContext> context, WaveShaperOptions const& options)
    : AudioNode(realm, context, options)
{
    // Set curve if provided in options
    if (options.curve.has_value())
        set_curve(options.curve.value());
    
    // Set oversample if provided in options
    if (options.oversample.has_value())
        m_oversample = options.oversample.value();
}

WaveShaperNode::~WaveShaperNode() = default;

WebIDL::ExceptionOr<GC::Ref<WaveShaperNode>> WaveShaperNode::create(JS::Realm& realm, GC::Ref<BaseAudioContext> context, WaveShaperOptions const& options)
{
    return construct_impl(realm, context, options);
}

// https://webaudio.github.io/web-audio-api/#dom-waveshapernode-waveshapernode
WebIDL::ExceptionOr<GC::Ref<WaveShaperNode>> WaveShaperNode::construct_impl(JS::Realm& realm, GC::Ref<BaseAudioContext> context, WaveShaperOptions const& options)
{
    // FIXME: If the curve array has less than 2 values, throw an InvalidStateError and abort these steps.
    
    auto node = realm.create<WaveShaperNode>(realm, context, options);
    
    // FIXME: Initialize the control message to set the internal curve and oversample attributes

    return node;
}

void WaveShaperNode::initialize(JS::Realm& realm)
{
    Base::initialize(realm);
    WEB_SET_PROTOTYPE_FOR_INTERFACE(WaveShaperNode);
}

void WaveShaperNode::visit_edges(Cell::Visitor& visitor)
{
    Base::visit_edges(visitor);
    visitor.visit(m_curve);
}

// https://webaudio.github.io/web-audio-api/#dom-waveshapernode-curve
void WaveShaperNode::set_curve(GC::Ptr<WebIDL::Float32Array> curve)
{
    // FIXME: If the array has less than 2 values, throw an InvalidStateError and abort these steps.
    
    m_curve = curve;
    
    // FIXME: Set the internal curve attribute to the given curve.
    // FIXME: Queue a control message to set the curve on the audio thread.
}

}