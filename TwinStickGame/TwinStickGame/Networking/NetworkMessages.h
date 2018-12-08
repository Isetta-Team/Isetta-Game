#pragma once
#include <IsettaEngine.h>

DEFINE_NETWORK_MESSAGE(SpawnPlayerMessage)
template <typename Stream>
bool Serialize(Stream* stream) {
  serialize_int(stream, netId, 0, 1000);
  serialize_int(stream, clientAuthorityId, 0,
                Isetta::NetworkManager::Instance().GetMaxClients());
  serialize_string(stream, playerName, sizeof playerName);
  serialize_float(stream, startPos.x);
  serialize_float(stream, startPos.y);
  serialize_float(stream, startPos.z);
  return true;
}

void Copy(const yojimbo::Message* otherMessage) override {
  auto* message = reinterpret_cast<const SpawnPlayerMessage*>(otherMessage);
  netId = message->netId;
  clientAuthorityId = message->clientAuthorityId;
  strcpy_s(playerName, message->playerName);
  startPos = message->startPos;
}

int netId = 0;
int clientAuthorityId = 0;
char playerName[32];
Isetta::Math::Vector3 startPos = Isetta::Math::Vector3::zero;
DEFINE_NETWORK_MESSAGE_END

DEFINE_NETWORK_MESSAGE(LevelLoadedMessage)
template <typename Stream>
bool Serialize(Stream* stream) {
  return true;
}

void Copy(const yojimbo::Message* otherMessage) override {}

DEFINE_NETWORK_MESSAGE_END

DEFINE_NETWORK_MESSAGE(AllPlayerReadyMessage)
template <typename Stream>
bool Serialize(Stream* stream) {
  serialize_int(stream, playerCount, 0, 100);
  return true;
}

void Copy(const yojimbo::Message* otherMessage) override {
  auto* message = reinterpret_cast<const AllPlayerReadyMessage*>(otherMessage);
  playerCount = message->playerCount;
}
int playerCount = 0;
DEFINE_NETWORK_MESSAGE_END

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
  serialize_float(stream, damage);
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
  damage = message->damage;
  bulletIndex = message->bulletIndex;
  playerIndex = message->playerIndex;
}

Math::Vector3 startPos{};
Math::Vector3 dir{};
float speed{0.f};
float range{0.f};
float damage{0.f};
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
  serialize_float(stream, damage);
  return true;
}

void Copy(const yojimbo::Message* otherMessage) override {
  auto* message = reinterpret_cast<const HitEnemyMessage*>(otherMessage);
  playerIndex = message->playerIndex;
  enemyIndex = message->enemyIndex;
  damage = message->damage;
}

int playerIndex = 0;
int enemyIndex = 0;
float damage = 0.f;
DEFINE_NETWORK_MESSAGE_END

DEFINE_NETWORK_MESSAGE(InitializeEnemyMessage)
template <typename Stream>
bool Serialize(Stream* stream) {
  serialize_float(stream, localScale.x);
  serialize_float(stream, localScale.y);
  serialize_float(stream, localScale.z);
  serialize_int(stream, networkId, 0, 10000);
  serialize_int(stream, index, 0, 10000);
  return true;
}

void Copy(const yojimbo::Message* otherMessage) override {
  auto* message = reinterpret_cast<const InitializeEnemyMessage*>(otherMessage);
  localScale = message->localScale;
  networkId = message->networkId;
  index = message->index;
}

Math::Vector3 localScale {};
int networkId = 0;
int index = 0;
DEFINE_NETWORK_MESSAGE_END

DEFINE_NETWORK_MESSAGE(RespawnEnemyMessage)
template <typename Stream>
bool Serialize(Stream* stream) {
  serialize_int(stream, enemyIndex, 0, 10000);
  serialize_float(stream, spawnPos.x);
  serialize_float(stream, spawnPos.y);
  serialize_float(stream, spawnPos.z);
  return true;
}

void Copy(const yojimbo::Message* otherMessage) override {
  auto* message = reinterpret_cast<const RespawnEnemyMessage*>(otherMessage);
  enemyIndex = message->enemyIndex;
  spawnPos = message->spawnPos;
}

int enemyIndex = 0;
Math::Vector3 spawnPos{};
DEFINE_NETWORK_MESSAGE_END

DEFINE_NETWORK_MESSAGE(DeactivateBulletMessage)
template <typename Stream>
bool Serialize(Stream* stream) {
  serialize_int(stream, bulletIndex, 0, 10000);
  return true;
}

void Copy(const yojimbo::Message* otherMessage) override {
  auto* message = reinterpret_cast<const DeactivateBulletMessage*>(otherMessage);
  bulletIndex = message->bulletIndex;
}

int bulletIndex = 0;
DEFINE_NETWORK_MESSAGE_END

DEFINE_NETWORK_MESSAGE(ScoreMessage)
template <typename Stream>
bool Serialize(Stream* stream) {
  serialize_float(stream, score);
  serialize_int(stream, playerIndex, 0, 10000);
  return true;
}

void Copy(const yojimbo::Message* otherMessage) override {
  auto* message = reinterpret_cast<const ScoreMessage*>(otherMessage);
  score = message->score;
  playerIndex = message->playerIndex;
}

float score = 0;
int playerIndex = 0;
DEFINE_NETWORK_MESSAGE_END

DEFINE_NETWORK_MESSAGE(PlayerLifeMessage)
template <typename Stream>
bool Serialize(Stream* stream) {
  serialize_int(stream, state, 0, 10);
  serialize_int(stream, playerIndex, 0, 10000);
  return true;
}

void Copy(const yojimbo::Message* otherMessage) override {
  auto* message = reinterpret_cast<const PlayerLifeMessage*>(otherMessage);
  state = message->state;
  playerIndex = message->playerIndex;
}

int state = 0; // 1 - die, 2 - revive
int playerIndex = 0;
DEFINE_NETWORK_MESSAGE_END

DEFINE_NETWORK_MESSAGE(PlayerDamageMessage)
template <typename Stream>
bool Serialize(Stream* stream) {
  serialize_float(stream, damage);
  serialize_int(stream, playerIndex, 0, 10000);
  return true;
}

void Copy(const yojimbo::Message* otherMessage) override {
  auto* message = reinterpret_cast<const PlayerDamageMessage*>(otherMessage);
  damage = message->damage;
  playerIndex = message->playerIndex;
}

float damage = 0;
int playerIndex = 0;
DEFINE_NETWORK_MESSAGE_END

DEFINE_NETWORK_MESSAGE(EnemyStateChangeMessage)
template <typename Stream>
bool Serialize(Stream* stream) {
  serialize_float(stream, newState);
  serialize_int(stream, enemyIndex, 0, 10000);
  return true;
}

void Copy(const yojimbo::Message* otherMessage) override {
  auto* message = reinterpret_cast<const EnemyStateChangeMessage*>(otherMessage);
  newState = message->newState;
  enemyIndex = message->enemyIndex;
}

int newState = 0;
int enemyIndex = 0;
DEFINE_NETWORK_MESSAGE_END