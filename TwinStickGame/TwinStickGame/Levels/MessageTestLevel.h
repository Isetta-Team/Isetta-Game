/*
 * Copyright (c) 2018 Isetta
 */
#pragma once

#include "Core/IsettaCore.h"
#include "External/yojimbo/yojimbo.h"
#include "Networking/Messages.h"

using namespace Isetta;

DEFINE_LEVEL(MessageTestLevel)
void Load() override;
DEFINE_LEVEL_END

DEFINE_NETWORK_MESSAGE(TestingMessage)
template <typename Stream>
bool Serialize(Stream* stream) {
  serialize_int(stream, number, 0, 10000);
  return true;
}

void Copy(const yojimbo::Message* otherMessage) override {
  const TestingMessage* message =
      reinterpret_cast<const TestingMessage*>(otherMessage);
  number = message->number;
}

int number = 0;
DEFINE_NETWORK_MESSAGE_END