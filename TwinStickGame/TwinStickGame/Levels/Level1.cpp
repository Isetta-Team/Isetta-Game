/*
 * Copyright (c) 2018 Isetta
 */
#include <IsettaEngine.h>

#include "Levels/Level1.h"

#include <Components/Editor/EditorComponent.h>
#include "Enemy/EnemyManager.h"
#include "Gameplay/BulletManager.h"
#include "Gameplay/GameManager.h"
#include "Player/CameraController.h"

void Level1::Load() {
  Entity* camera = Entity::Instantiate("Camera");
  camera->AddComponent<CameraComponent>();
  camera->AddComponent<CameraController>();
  camera->AddComponent<AudioListener>();
  camera->transform->SetWorldPos({15, 15, -30});
  camera->transform->LookAt(Math::Vector3::zero);

  // temp. instantiate the ground
  level1Map.Load();

  Entity* enemyManager = Entity::Instantiate("Enemy Manager");
  enemyManager->AddComponent<EnemyManager>();
  enemyManager->AddComponent<EditorComponent>();

  Entity* bulletManager = Entity::Instantiate("Bullet Manager");
  bulletManager->AddComponent<BulletManager>();

  Input::RegisterKeyPressCallback(KeyCode::ESCAPE,
                                  []() { Application::Exit(); });

  GameManager::Instance().SendLevelLoadedMessage();
}
