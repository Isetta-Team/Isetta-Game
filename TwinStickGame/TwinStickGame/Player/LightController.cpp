/*
 * Copyright (c) 2018 Isetta
 */
#include <IsettaEngine.h>

#include "Player/LightController.h"

using namespace Isetta;

void LightController::Update() {
  if (player) {
    offset = {0.1, 3, 0};
    transform->SetWorldPos(player->transform->GetWorldPos() + offset);
    transform->LookAt(transform->GetWorldPos() -
                      player->transform->GetWorldPos() +
                      transform->GetWorldPos());
  }
}
