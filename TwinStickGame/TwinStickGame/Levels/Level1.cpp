/*
 * Copyright (c) 2018 Isetta
 */

#include "Levels/Level1.h"

#include <Components/FlyController.h>
#include <Core/IsettaCore.h>

#include "Gameplay/EntityFactory.h"
#include "Gameplay/GameManager.h"

void Level1::Load() {
  Entity* camera = Entity::Instantiate("Camera");
  camera->AddComponent<CameraComponent>();
  camera->transform->SetWorldPos({15, 15, 30});
  camera->transform->LookAt(Math::Vector3::zero);
  camera->AddComponent<FlyController>();

  Entity* lightEntity{Entity::Instantiate("Light")};
  lightEntity->AddComponent<LightComponent>();
  lightEntity->SetTransform(Math::Vector3{0, 200, 600},
                            Math::Vector3{-30, 0, 0});

    // instantiate the ground
  Entity* ground{Entity::Instantiate("Ground")};
  ground->AddComponent<MeshComponent>("models/Ground/Level.scene.xml");
  ground->transform->SetWorldPos({0, -0.01f, 0});

  // Spawn the scene
  // Entity* ground = Primitive::Create(Primitive::Type::Cube);
  // ground->transform->SetLocalScale({50, 0.1, 50});
  // ground->transform->SetWorldPos({0, -0.051, 0});

  // Spawn an enemy spawner

  // Spawn a score tracker

  // Spawn an UI manager?

  // Spawn a player

  // Tests
  EntityFactory::CreateNetworkEntity();
  EntityFactory::CreateDebugEntity();

  Input::RegisterKeyPressCallback(KeyCode::ESCAPE,
                                  []() { Application::Exit(); });

  GameManager::Instance().SendLevelLoadedMessage();
}
