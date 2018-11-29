#pragma once
#include "Networking/Messages.h"
#include "Core/Config/Config.h"

RPC_MESSAGE_DEFINE(ClientConnectedMessage)
template <typename Stream>
bool Serialize(Stream* stream) {
  serialize_string(stream, ip, sizeof(ip));
  serialize_string(stream, machineName, sizeof(machineName));
  serialize_int(stream, clientIndex, 0, CONFIG_VAL(networkConfig.maxClients));
  return true;
}

void Copy(const yojimbo::Message* otherMessage) override {
  const ClientConnectedMessage* message =
      reinterpret_cast<const ClientConnectedMessage*>(otherMessage);

  strcpy_s(ip, message->ip);
  strcpy_s(machineName, message->machineName);
  clientIndex = message->clientIndex;
}

char ip[16];
char machineName[16];
int clientIndex;

RPC_MESSAGE_FINISH

RPC_MESSAGE_DEFINE(LoadLevelMessage)
template <typename Stream>
bool Serialize(Stream* stream) {
  serialize_string(stream, levelName, sizeof(levelName));
  return true;
}

void Copy(const yojimbo::Message* otherMessage) override {
  auto* message = reinterpret_cast<const LoadLevelMessage*>(otherMessage);
  strcpy_s(levelName, message->levelName);
}

char levelName[64];

public:
inline const static int levelNameMaxLength = 64;
RPC_MESSAGE_FINISH
