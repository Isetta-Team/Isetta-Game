#pragma once
#include "Networking/Messages.h"

using namespace Isetta;

DEFINE_NETWORK_MESSAGE(ShootMessage)
template <typename Stream>
bool Serialize(Stream* stream) {
  serialize_float(stream, startPos.x);
  serialize_float(stream, startPos.y);
  serialize_float(stream, startPos.z);
  serialize_float(stream, dir.x);
  serialize_float(stream, dir.y);
  serialize_float(stream, dir.z);
  serialize_int(stream, playerNetId, 0, 10000);
  return true;
}

void Copy(const yojimbo::Message* otherMessage) override {
  auto* message = reinterpret_cast<const ShootMessage*>(otherMessage);
  startPos = message->startPos;
  dir = message->dir;
  playerNetId = message->playerNetId;
}

Math::Vector3 startPos{};
Math::Vector3 dir{};
int playerNetId = 0;
DEFINE_NETWORK_MESSAGE_END

DEFINE_NETWORK_MESSAGE(PlayerStateChangeMessage)
template <typename Stream>
bool Serialize(Stream* stream) {
  serialize_int(stream, playerIndex, 0, 100);
  serialize_int(stream, newState, 0, 10);
  return true;
}

void Copy(const yojimbo::Message* otherMessage) override {
  auto* message = reinterpret_cast<const PlayerStateChangeMessage*>(otherMessage);
  playerIndex = message->playerIndex;
  newState = message->newState;
}

int playerIndex = 0;
int newState = 0;
DEFINE_NETWORK_MESSAGE_END