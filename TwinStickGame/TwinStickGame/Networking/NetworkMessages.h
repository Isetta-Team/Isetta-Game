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
  return true;
}

void Copy(const yojimbo::Message* otherMessage) override {}
DEFINE_NETWORK_MESSAGE_END