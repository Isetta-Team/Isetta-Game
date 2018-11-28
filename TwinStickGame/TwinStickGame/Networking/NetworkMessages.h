#pragma once
#include "Networking/Messages.h"

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

char levelName[32];
RPC_MESSAGE_FINISH

RPC_MESSAGE_DEFINE(LevelLoadedMessage)
template <typename Stream>
bool Serialize(Stream* stream) {
  return true;
}

void Copy(const yojimbo::Message* otherMessage) override {
  auto* message = reinterpret_cast<const LevelLoadedMessage*>(otherMessage);
}

RPC_MESSAGE_FINISH
