///*
// * Copyright (c) 2018 Isetta
// */
//#include "PlayerController.h"
//
//// ENGINE
//#include "Custom/IsettaCore.h"
//#include "Graphics/AnimationComponent.h"
//
// namespace Isetta {
// PlayerController* PlayerController::instance;
//
// void PlayerController::OnEnable() { instance = this; }
// void PlayerController::OnDisable() { instance = nullptr; }
//
// void PlayerController::Start() {
//  animationComp = entity->GetComponent<AnimationComponent>();
//}
//
// void PlayerController::Update() {
//  float dt = Time::GetDeltaTime();
//  Math::Vector3 lookDir;
//  Math::Vector3 movement{};
//
//  movement +=
//      Input::GetGamepadAxis(GamepadAxis::L_HORIZONTAL) * Math::Vector3::left +
//      Input::GetGamepadAxis(GamepadAxis::L_VERTICLE) * Math::Vector3::forward;
//
//  if (movement.Magnitude() > 1) {
//    movement.Normalize();
//  }
//
//  if (movement.Magnitude() > 0) {
//    if (!isMoving) {
//      isMoving = true;
//      animationComp->TransitToAnimationState(1, 0.2f);
//    }
//    GetTransform()->TranslateWorld(movement * moveSpeed * dt);
//  } else {
//    if (isMoving) {
//      isMoving = false;
//      animationComp->TransitToAnimationState(0, 0.2f);
//    }
//  }
//
//  lookDir +=
//      Input::GetGamepadAxis(GamepadAxis::R_HORIZONTAL) * Math::Vector3::left +
//      Input::GetGamepadAxis(GamepadAxis::R_VERTICLE) * Math::Vector3::forward;
//
//  if (lookDir.Magnitude() >= 1.f) {
//    lookDir.Normalize();
//    GetTransform()->LookAt(GetTransform()->GetWorldPos() + lookDir);
//  }
//}
//
// PlayerController* PlayerController::Instance() { return instance; }
//
//}  // namespace Isetta
