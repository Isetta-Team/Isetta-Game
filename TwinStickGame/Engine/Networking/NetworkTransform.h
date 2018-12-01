/*
 * Copyright (c) 2018 Isetta
 */
#pragma once
#include "Core/Config/Config.h"
#include "Core/Math/Math.h"
#include "ISETTA_API.h"
#include "Networking/Messages.h"
#include "Scene/Component.h"

namespace Isetta {
DEFINE_COMPONENT(NetworkTransform, Component, true)
public:
void Start() override;
void Update() override;
void FixedUpdate() override;

/**
 * @brief Forcefully sends a transform over the network to be updated.
 *
 * @param snap Determines whether the transform should be snapped to
 */
void ForceSendTransform(bool snap = false);
/**
 * @brief Snaps our transform to its target position and stops interpolating.
 *
 */
void SnapLocalTransform();
/**
 * @brief Sets the parent of our entity to the entity corresponding to the given
 * network ID.
 *
 * @param netId The network ID corresponding to the entity who we should parent
 * to ourself
 * @return true if the entity with the given network ID exists
 */
bool SetNetworkedParent(int netId);
/**
 * @brief Unsets the parent of our entity
 *
 */
void SetNetworkedParentToRoot();

/// Distance that the entity needs to move before sending a network message for position
float updateDistance = .01;
/// Angle that the entity needs to rotate before sending a network message for rotation
float updateRotation = 5;
/// Size that the entity needs to scale before sending a network message for scale
float updateScale = .005;
/// Distance that the entity can move from our current position until our transform snaps to its target position
float snapDistance = 5;
/// Angle that the entity can rotate from our current rotation before our transform snaps to its target rotation
float snapRotation = 30;
/// Size that the entityi can scale from our current scale before our transform snaps to its target scale
float snapScale = 1;

private:
int updateCounter = 0;
float lastPosMessage = 0;
float lastRotMessage = 0;
float lastScaleMessage = 0;

float posInterpolation = 1;
float rotInterpolation = 1;
float scaleInterpolation = 1;

Math::Vector3 targetPos;
Math::Vector3 prevPos;
Math::Quaternion targetRot = Math::Quaternion::identity;
Math::Quaternion prevRot = Math::Quaternion::identity;
Math::Vector3 targetScale;
Math::Vector3 prevScale;

static bool registeredCallbacks;
static std::unordered_map<int, float> serverPosTimestamps;
static std::unordered_map<int, float> serverRotTimestamps;
static std::unordered_map<int, float> serverScaleTimestamps;
class NetworkId* netId;
friend class NetworkTransform;
friend class NetworkManager;
DEFINE_COMPONENT_END(NetworkTransform, Component)

// TODO(Caleb): ParentMessage
DEFINE_NETWORK_MESSAGE(ParentMessage)
template <typename Stream>
bool Serialize(Stream* stream) {
  serialize_int(stream, netId, 0,
                Config::Instance().networkConfig.maxNetID.GetVal());
  serialize_int(stream, parentNetId, 0,
                Config::Instance().networkConfig.maxNetID.GetVal());
  return true;
}

void Copy(const yojimbo::Message* otherMessage) override {
  const ParentMessage* message =
      reinterpret_cast<const ParentMessage*>(otherMessage);

  netId = message->netId;
  parentNetId = message->parentNetId;
}

int netId = 0;
int parentNetId = 0;

DEFINE_NETWORK_MESSAGE_END

DEFINE_NETWORK_MESSAGE(PositionMessage)
template <typename Stream>
bool Serialize(Stream* stream) {
  serialize_int(stream, netId, 0,
                Config::Instance().networkConfig.maxNetID.GetVal());

  serialize_float(stream, timestamp);

  serialize_float(stream, localPos.x);
  serialize_float(stream, localPos.y);
  serialize_float(stream, localPos.z);
  return true;
}

void Copy(const yojimbo::Message* otherMessage) override {
  const PositionMessage* message =
      reinterpret_cast<const PositionMessage*>(otherMessage);

  netId = message->netId;
  timestamp = message->timestamp;
  localPos = message->localPos;
}

public:
int netId = 0;
float timestamp = 0;
Math::Vector3 localPos;
DEFINE_NETWORK_MESSAGE_END

DEFINE_NETWORK_MESSAGE(RotationMessage)
template <typename Stream>
bool Serialize(Stream* stream) {
  serialize_int(stream, netId, 0,
                Config::Instance().networkConfig.maxNetID.GetVal());

  serialize_float(stream, timestamp);

  serialize_float(stream, localRot.x);
  serialize_float(stream, localRot.y);
  serialize_float(stream, localRot.z);
  serialize_float(stream, localRot.w);
  return true;
}

void Copy(const yojimbo::Message* otherMessage) override {
  const RotationMessage* message =
      reinterpret_cast<const RotationMessage*>(otherMessage);

  netId = message->netId;
  timestamp = message->timestamp;
  localRot = message->localRot;
}

public:
int netId = 0;
float timestamp = 0;
Math::Quaternion localRot;
DEFINE_NETWORK_MESSAGE_END

DEFINE_NETWORK_MESSAGE(ScaleMessage)
template <typename Stream>
bool Serialize(Stream* stream) {
  serialize_int(stream, netId, 0,
                Config::Instance().networkConfig.maxNetID.GetVal());

  serialize_float(stream, timestamp);

  serialize_float(stream, localScale.x);
  serialize_float(stream, localScale.y);
  serialize_float(stream, localScale.z);
  return true;
}

void Copy(const yojimbo::Message* otherMessage) override {
  const ScaleMessage* message =
      reinterpret_cast<const ScaleMessage*>(otherMessage);

  netId = message->netId;
  timestamp = message->timestamp;
  localScale = message->localScale;
}

public:
int netId = 0;
float timestamp = 0;
Math::Vector3 localScale;
DEFINE_NETWORK_MESSAGE_END

DEFINE_NETWORK_MESSAGE(TransformMessage)
template <typename Stream>
bool Serialize(Stream* stream) {
  serialize_int(stream, netId, 0,
                Config::Instance().networkConfig.maxNetID.GetVal());

  serialize_float(stream, timestamp);

  serialize_bool(stream, snap);

  serialize_float(stream, localPos.x);
  serialize_float(stream, localPos.y);
  serialize_float(stream, localPos.z);

  serialize_float(stream, localRot.x);
  serialize_float(stream, localRot.y);
  serialize_float(stream, localRot.z);
  serialize_float(stream, localRot.w);

  serialize_float(stream, localScale.x);
  serialize_float(stream, localScale.y);
  serialize_float(stream, localScale.z);
  return true;
}

void Copy(const yojimbo::Message* otherMessage) override {
  const TransformMessage* message =
      reinterpret_cast<const TransformMessage*>(otherMessage);

  netId = message->netId;
  timestamp = message->timestamp;
  snap = message->snap;
  localPos = message->localPos;
  localRot = message->localRot;
  localScale = message->localScale;
}

public:
int netId = 0;
float timestamp = 0;
bool snap = false;
Math::Vector3 localPos;
Math::Quaternion localRot;
Math::Vector3 localScale;
DEFINE_NETWORK_MESSAGE_END

}  // namespace Isetta
