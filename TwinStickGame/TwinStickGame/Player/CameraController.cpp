/*
 * Copyright (c) 2018 Isetta
 */
#include <IsettaEngine.h>

#include "Gameplay/GameManager.h"
#include "Player/CameraController.h"

using namespace Isetta;

void CameraController::Update() {
  auto* player = GameManager::Instance().GetLocalPlayer();
  if (player) {
    transform->SetWorldPos(player->transform->GetWorldPos() + offset);
    transform->LookAt(transform->GetWorldPos() -
                      player->transform->GetWorldPos() +
                      transform->GetWorldPos());
  }
}

void CameraController::GuiUpdate() {
  static bool isOpen = true;
  GUI::Window(
      RectTransform{
          {-100, 400, 500, 100}, GUI::Pivot::TopRight, GUI::Pivot::TopRight},
      "Camera Controller",
      [this]() {
        float y = 5, x = 5, height = 20, width = 250;
        GUI::InputVector3(RectTransform{{x, y, width, height}},
                          "Camera offset ", &offset);
      },
      &isOpen);
}
