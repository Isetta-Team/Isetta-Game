/*
 * Copyright (c) 2018 Isetta
 */
#include "Player/PlayerController.h"

#include <Core/IsettaCore.h>
#include <Networking/NetworkId.h>
#include "Gameplay/InputManager.h"

void PlayerController::Start() {
  networkId = entity->GetComponent<NetworkId>();
}

void PlayerController::Update() {
  DebugDraw::WireCapsule(transform->GetLocalToWorldMatrix(), 0.5f, 2.f,
                         Color::green);

  if (!networkId->HasClientAuthority()) {
    return;
  }

  Move();
}

void PlayerController::Move() {
  float dt = Time::GetDeltaTime();

  Math::Vector3 movement{InputManager::GetMovementInput().x, 0,
                         InputManager::GetMovementInput().y};

  if (movement.Magnitude() > 1) {
    movement.Normalize();
  }

  if (movement.Magnitude() > 0) {
    if (!isMoving) {
      isMoving = true;
    }
    transform->TranslateWorld(movement * moveSpeed * dt);
  } else {
    if (isMoving) {
      isMoving = false;
    }
  }

  Math::Vector3 lookDir{InputManager::GetShootInput().x, 0,
                        InputManager::GetShootInput().y};

  if (lookDir.Magnitude() >= 1.f) {
    lookDir.Normalize();
    transform->LookAt(transform->GetWorldPos() + lookDir);
  }
}
