/*
 * Copyright (c) 2018 Isetta
 */
#include "SinglePlayerLevel.h"

// ENGINE
#include "Core/Config/Config.h"
#include "Graphics/CameraComponent.h"
#include "Graphics/GUI.h"
#include "Scene/Entity.h"

// GAME
#include "Gameplay/Damageable.h"
#include "Gameplay/Score.h"
#include "Player/PlayerHealth.h"

using namespace Isetta;
using CameraProperty = CameraComponent::Property;

void SinglePlayerLevel::LoadLevel() {
  // TODO: remove
  GUI::AddFontFromFile("Resources\\fonts\\NeonAbsoluteSans.ttf", 50.f, "Neon");

  Entity* cameraEntity{AddEntity("Camera")};
  CameraComponent* camComp =
      cameraEntity->AddComponent<CameraComponent, true>("Camera");
  cameraEntity->SetTransform(Math::Vector3{0, 5, 10}, Math::Vector3{-15, 0, 0},
                             Math::Vector3::one);
  camComp->SetProperty<CameraProperty::FOV>(
      CONFIG_VAL(renderConfig.fieldOfView));
  camComp->SetProperty<CameraProperty::NEAR_PLANE>(
      CONFIG_VAL(renderConfig.nearClippingPlane));
  camComp->SetProperty<CameraProperty::FAR_PLANE>(
      CONFIG_VAL(renderConfig.farClippingPlane));

  Entity* score{AddEntity("Score")};
  score->AddComponent<Score>();

  Entity* player{AddEntity("Player")};
  player->AddComponent<Damageable>(100);
  player->AddComponent<PlayerHealth>();
}
