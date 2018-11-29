/*
 * Copyright (c) 2018 Isetta
 */
#include "HitscanTestLevel.h"
#include "Core/IsettaCore.h"

#include "Components/Editor/EditorComponent.h"
#include "Components/Editor/FrameReporter.h"
#include "Components/GridComponent.h"

#include "Collisions/BoxCollider.h"
#include "Collisions/CapsuleCollider.h"
#include "Collisions/SphereCollider.h"
#include "Scene/Primitive.h"

#include "Gameplay/Hitscan.h"
#include "Test/HitscanTest.h"

void HitscanTestLevel::Load() {
  Entity* cameraEntity = Entity::Instantiate("Camera");
  cameraEntity->AddComponent<CameraComponent>();
  cameraEntity->SetTransform(Math::Vector3{0, 10, 0}, Math::Vector3{-90, 0, 0},
                             Math::Vector3::one);

  Entity* testEntity = Entity::Instantiate("Hitscanner");
  testEntity->AddComponent<Hitscan>();
  testEntity->AddComponent<HitscanTest>();

  Entity* debug = Entity::Instantiate("Debug");
  debug->AddComponent<GridComponent>();
  debug->AddComponent<FrameReporter>()->Open();
  debug->AddComponent<EditorComponent>();

  Entity* colEnt = Entity::Instantiate("Collider 1");
  colEnt->SetTransform(Math::Vector3(2, 0, 2));
  SphereCollider* sphere = colEnt->AddComponent<SphereCollider>();

  colEnt = Entity::Instantiate("Collider 2");
  colEnt->SetTransform(Math::Vector3(-2, 0, -2));
  CapsuleCollider* capsule = colEnt->AddComponent<CapsuleCollider>();

  colEnt = Entity::Instantiate("Collider 3");
  colEnt->SetTransform(Math::Vector3(3, 0, 0));
  BoxCollider* box = colEnt->AddComponent<BoxCollider>();
}