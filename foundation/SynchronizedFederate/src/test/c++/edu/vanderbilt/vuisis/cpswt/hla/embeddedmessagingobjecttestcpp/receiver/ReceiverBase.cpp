/*
 * Certain portions of this software are Copyright (C) 2006-present
 * Vanderbilt University, Institute for Software Integrated Systems.
 *
 * Certain portions of this software are contributed as a public service by
 * The National Institute of Standards and Technology (NIST) and are not
 * subject to U.S. Copyright.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above Vanderbilt University copyright notice, NIST contribution
 * notice and this permission and disclaimer notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE. THE AUTHORS OR COPYRIGHT HOLDERS SHALL NOT HAVE
 * ANY OBLIGATION TO PROVIDE MAINTENANCE, SUPPORT, UPDATES, ENHANCEMENTS,
 * OR MODIFICATIONS.
 */



#include "edu/vanderbilt/vuisis/cpswt/hla/embeddedmessagingobjecttestcpp/receiver/ReceiverBase.hpp"


#if __cplusplus >= 201703L
#define MultiArgThrow17
#define Throw17 noexcept
#define throw(...) __VA_OPT__(MultiArg)##Throw17
#endif

namespace edu {
 namespace vanderbilt {
  namespace vuisis {
   namespace cpswt {
    namespace hla {
     namespace embeddedmessagingobjecttestcpp {
      namespace receiver {


// constructor
void ReceiverBase::init() {
    createRTI();
    joinFederation();

    enableTimeConstrained();
    enableTimeRegulation(getLookahead());

    // INTERACTION SUBSCRIPTIONS

    ::edu::vanderbilt::vuisis::cpswt::hla::InteractionRoot_p::C2WInteractionRoot_p::EmbeddedMessaging_p::Receiver::subscribe_interaction(getRTI());

    // SOFT OBJECT SUBSCRIPTIONS
    ::edu::vanderbilt::vuisis::cpswt::hla::ObjectRoot_p::TestObject::soft_subscribe_attribute("ObjectRoot.TestObject", "IntValue");
    ::edu::vanderbilt::vuisis::cpswt::hla::ObjectRoot_p::TestObject::soft_subscribe_attribute("ObjectRoot.TestObject", "JSONValue2");
    ::edu::vanderbilt::vuisis::cpswt::hla::ObjectRoot_p::TestObject::soft_subscribe_attribute("ObjectRoot.TestObject", "LongValue");
    ::edu::vanderbilt::vuisis::cpswt::hla::ObjectRoot_p::TestObject::soft_subscribe_attribute("ObjectRoot.TestObject", "ShortValue");
    ::edu::vanderbilt::vuisis::cpswt::hla::ObjectRoot_p::TestObject::soft_subscribe_attribute("ObjectRoot.TestObject", "StringValue");
    ::edu::vanderbilt::vuisis::cpswt::hla::ObjectRoot_p::TestObject::soft_subscribe_object(getRTI());

    // DIRECT OBJECT SUBSCRIPTIONS
    ::edu::vanderbilt::vuisis::cpswt::hla::ObjectRoot_p::TestObject::subscribe_attribute("ObjectRoot.TestObject", "BoolValue2");
    ::edu::vanderbilt::vuisis::cpswt::hla::ObjectRoot_p::TestObject::subscribe_attribute("ObjectRoot.TestObject", "ByteValue");
    ::edu::vanderbilt::vuisis::cpswt::hla::ObjectRoot_p::TestObject::subscribe_attribute("ObjectRoot.TestObject", "CharValue");
    ::edu::vanderbilt::vuisis::cpswt::hla::ObjectRoot_p::TestObject::subscribe_attribute("ObjectRoot.TestObject", "DoubleValue");
    ::edu::vanderbilt::vuisis::cpswt::hla::ObjectRoot_p::TestObject::subscribe_attribute("ObjectRoot.TestObject", "JSONValue1");

    ::edu::vanderbilt::vuisis::cpswt::hla::ObjectRoot_p::TestObject::subscribe_object(getRTI());
}

ReceiverBase::ReceiverBase(FederateConfig *federateConfig): Super(federateConfig) {
    init();
}

void ReceiverBase::receiveInteraction(
  RTI::InteractionClassHandle interactionClassHandle,
  const RTI::ParameterHandleValuePairSet& parameterHandleValuePairSet,
  const char *userSuppliedTag
) throw (
  RTI::InteractionClassNotKnown,
  RTI::InteractionParameterNotKnown,
  RTI::FederateInternalError
) {
    if (getMoreATRs()) {
        ::edu::vanderbilt::vuisis::cpswt::hla::InteractionRoot::SP interactionRootSP =
          ::edu::vanderbilt::vuisis::cpswt::hla::InteractionRoot::create_interaction(
            interactionClassHandle, parameterHandleValuePairSet
          );

        C2WInteractionRoot::SP c2wInteractionRootSP =
          boost::dynamic_pointer_cast<C2WInteractionRoot>(interactionRootSP);
        if (c2wInteractionRootSP) {
            // Filter interaction if src/origin fed requirements (if any) are not met
            if ( _subscribedInteractionFilter.filterC2WInteraction( getFederateId(), c2wInteractionRootSP ) ) {
                return;
            }
        }
        Super::receiveInteraction(interactionClassHandle, parameterHandleValuePairSet, userSuppliedTag);
    }
}

void ReceiverBase::receiveInteraction(
  RTI::InteractionClassHandle interactionClassHandle,
  const RTI::ParameterHandleValuePairSet &parameterHandleValuePairSet,
  const RTI::FedTime &fedTime,
  const char *userSuppliedTag,
  RTI::EventRetractionHandle eventRetractionHandle
) throw (
  RTI::InteractionClassNotKnown,
  RTI::InteractionParameterNotKnown,
  RTI::InvalidFederationTime,
  RTI::FederateInternalError
) {
    if (getMoreATRs()) {
        ::edu::vanderbilt::vuisis::cpswt::hla::InteractionRoot::SP interactionRootSP =
          ::edu::vanderbilt::vuisis::cpswt::hla::InteractionRoot::create_interaction(
            interactionClassHandle, parameterHandleValuePairSet, fedTime
          );

        C2WInteractionRoot::SP c2wInteractionRootSP =
          boost::dynamic_pointer_cast<C2WInteractionRoot>( interactionRootSP );
        if (c2wInteractionRootSP) {
            // Filter interaction if src/origin fed requirements (if any) are not met
            if ( _subscribedInteractionFilter.filterC2WInteraction( getFederateId(), c2wInteractionRootSP ) ) {
                return;
            }
        }
        Super::receiveInteraction(
            interactionClassHandle, parameterHandleValuePairSet, fedTime, userSuppliedTag, eventRetractionHandle
        );
    }
}
      } // NAMESPACE "receiver"
     } // NAMESPACE "embeddedmessagingobjecttestcpp"
    } // NAMESPACE "hla"
   } // NAMESPACE "cpswt"
  } // NAMESPACE "vuisis"
 } // NAMESPACE "vanderbilt"
} // NAMESPACE "edu"

#if __cplusplus >= 201703L
#undef MultiArgThrow17
#undef Throw17
#undef throw
#endif