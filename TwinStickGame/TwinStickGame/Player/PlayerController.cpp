/*
 * Copyright (c) 2018 Isetta
 */
#include <IsettaEngine.h>
#include "Player/PlayerController.h"

void PlayerController::Start() {
  networkId = entity->GetComponent<NetworkId>();
}

void PlayerController::Update() {
  if (!networkId->HasClientAuthority()) {
    return;
  }

  Move();
}

void PlayerController::Move() {
  float dt = Time::GetDeltaTime();
  Math::Vector3 lookDir;
  Math::Vector3 movement{};

  movement +=
      Input::GetGamepadAxis(GamepadAxis::L_HORIZONTAL) * Math::Vector3::left +
      Input::GetGamepadAxis(GamepadAxis::L_VERTICAL) * Math::Vector3::forward;

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

  lookDir +=
      Input::GetGamepadAxis(GamepadAxis::R_HORIZONTAL) * Math::Vector3::left +
      Input::GetGamepadAxis(GamepadAxis::R_VERTICAL) * Math::Vector3::forward;

  if (lookDir.Magnitude() >= 1.f) {
    lookDir.Normalize();
    transform->LookAt(transform->GetWorldPos() + lookDir);
  }
}
