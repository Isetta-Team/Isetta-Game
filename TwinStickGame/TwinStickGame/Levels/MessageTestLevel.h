/*
 * Copyright (c) 2018 Isetta
 */
#pragma once

#include "Core/IsettaCore.h"
#include "External/yojimbo/yojimbo.h"
#include "Networking/Messages.h"

using namespace Isetta;

CREATE_LEVEL(MessageTestLevel)
void Load() override;
CREATE_LEVEL_END

RPC_MESSAGE_DEFINE(TestingMessage)
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
RPC_MESSAGE_FINISH