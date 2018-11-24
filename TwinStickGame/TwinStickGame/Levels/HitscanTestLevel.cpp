/*
 * Copyright (c) 2018 Isetta
 */
#include "HitscanTestLevel.h"
#include "Core/IsettaCore.h"

#include "Collisions/SphereCollider.h"

#include "Gameplay/Hitscan.h"
#include "Tools/HitscanTest.h"

void HitscanTestLevel::OnLevelLoad() {
  Entity* cameraEntity = Entity::Instantiate("Camera");
  cameraEntity->AddComponent<CameraComponent>();
  cameraEntity->SetTransform(Math::Vector3{0, 5, 0}, Math::Vector3{-90, 0, 0},
                             Math::Vector3::one);

  Entity* testEntity = Entity::Instantiate("Hitscanner");
  testEntity->AddComponent<Hitscan>();
  testEntity->AddComponent<HitscanTest>();

  Entity* colEnt = Entity::Instantiate("Collider 1");
  colEnt->SetTransform(Math::Vector3(2, 0, 2));
  SphereCollider* sphere = colEnt->AddComponent<SphereCollider>();
}