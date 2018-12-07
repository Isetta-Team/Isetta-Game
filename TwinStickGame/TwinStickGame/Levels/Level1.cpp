/*
 * Copyright (c) 2018 Isetta
 */
#include <IsettaEngine.h>

#include "Levels/Level1.h"

#include "Enemy/EnemyController.h"
#include "Gameplay/EntityFactory.h"
#include "Gameplay/GameManager.h"
#include "Player/CameraController.h"
#include "Gameplay/BulletManager.h"

void Level1::Load() {
  Entity* camera = Entity::Instantiate("Camera");
  camera->AddComponent<CameraComponent>();
  camera->AddComponent<CameraController>();
  camera->transform->SetWorldPos({15, 15, 30});
  camera->transform->LookAt(Math::Vector3::zero);

  Entity* lightEntity{Entity::Instantiate("Light")};
  lightEntity->AddComponent<LightComponent>();
  lightEntity->SetTransform(Math::Vector3{0, 200, 600},
                            Math::Vector3{-30, 0, 0});

  // temp. instantiate the ground
  Entity* ground{Entity::Instantiate("Ground")};
  ground->AddComponent<MeshComponent>("models/Ground/Level.scene.xml");
  ground->transform->SetWorldPos({0, -0.01f, 0});

  // Spawn the scene

  // Spawn an enemy spawner
  Entity* enemy = Entity::Instantiate("Enemy");
  enemy->AddComponent<EnemyController>();
  enemy->transform->SetWorldPos({1, 0, 5});

  // Spawn a score tracker

  // Spawn an UI manager?

  Entity* bulletManager = Entity::Instantiate("Bullet Manager");
  bulletManager->AddComponent<BulletManager>();

  // Tests
  EntityFactory::CreateNetworkEntity();
  EntityFactory::CreateDebugEntity();

  Input::RegisterKeyPressCallback(KeyCode::ESCAPE,
                                  []() { Application::Exit(); });

  GameManager::Instance().SendLevelLoadedMessage();
}
