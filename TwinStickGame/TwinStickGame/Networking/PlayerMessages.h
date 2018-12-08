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
  serialize_float(stream, speed);
  serialize_float(stream, range);
  serialize_int(stream, bulletIndex, 0, 10000);
  serialize_int(stream, playerIndex, 0, 10000);
  return true;
}

void Copy(const yojimbo::Message* otherMessage) override {
  auto* message = reinterpret_cast<const ShootMessage*>(otherMessage);
  startPos = message->startPos;
  dir = message->dir;
  speed = message->speed;
  range = message->range;
  bulletIndex = message->bulletIndex;
  playerIndex = message->playerIndex;
}

Math::Vector3 startPos{};
Math::Vector3 dir{};
float speed{0.f};
float range{0.f};
int bulletIndex{0};
int playerIndex{0};
DEFINE_NETWORK_MESSAGE_END

DEFINE_NETWORK_MESSAGE(PlayerStateChangeMessage)
template <typename Stream>
bool Serialize(Stream* stream) {
  serialize_int(stream, playerIndex, 0, 100);
  serialize_int(stream, newState, 0, 10);
  return true;
}

void Copy(const yojimbo::Message* otherMessage) override {
  auto* message =
      reinterpret_cast<const PlayerStateChangeMessage*>(otherMessage);
  playerIndex = message->playerIndex;
  newState = message->newState;
}

int playerIndex = 0;
int newState = 0;
DEFINE_NETWORK_MESSAGE_END

DEFINE_NETWORK_MESSAGE(HitEnemyMessage)
template <typename Stream>
bool Serialize(Stream* stream) {
  serialize_int(stream, playerIndex, 0, 100);
  serialize_int(stream, enemyIndex, 0, 10000);
  serialize_int(stream, bulletIndex, 0, 10000);
  serialize_float(stream, damage);
  return true;
}

void Copy(const yojimbo::Message* otherMessage) override {
  auto* message = reinterpret_cast<const HitEnemyMessage*>(otherMessage);
  playerIndex = message->playerIndex;
  enemyIndex = message->enemyIndex;
  bulletIndex = message->bulletIndex;
  damage = message->damage;
}

int playerIndex = 0;
int enemyIndex = 0;
int bulletIndex = 0;
float damage = 0.f;
DEFINE_NETWORK_MESSAGE_END
