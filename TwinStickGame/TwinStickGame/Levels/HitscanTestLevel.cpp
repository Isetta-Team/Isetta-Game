/*
 * Copyright (c) 2018 Isetta
 */
#include "HitscanTestLevel.h"
#include "Core/IsettaCore.h"

#include "Gameplay/Hitscan.h"
#include "Tools/HitscanTest.h"

void HitscanTestLevel::OnLevelLoad() {
  Entity* cameraEntity = Entity::Instantiate("Camera");
  cameraEntity->AddComponent<CameraComponent>();
  cameraEntity->SetTransform(Math::Vector3{0, 0, 00}, Math::Vector3{-90, 0, 0},
                             Math::Vector3::one);

  Entity* testEntity = Entity::Instantiate("Hitscanner");
  testEntity->AddComponent<Hitscan>();
  testEntity->AddComponent<HitscanTest>();
}