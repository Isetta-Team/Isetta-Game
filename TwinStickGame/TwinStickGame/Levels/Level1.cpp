/*
 * Copyright (c) 2018 Isetta
 */
#include <IsettaEngine.h>

#include "Levels/Level1.h"

#include "Gameplay/EntityFactory.h"
#include "Gameplay/GameManager.h"
#include "Player/CameraController.h"
#include "Gameplay/BulletManager.h"
#include "Enemy/EnemyManager.h"
#include <Components/Editor/EditorComponent.h>
#include <Components/NetworkMonitor.h>

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
  BuildEnvironment();

  Entity* enemyManager = Entity::Instantiate("Enemy Manager");
  enemyManager->AddComponent<EnemyManager>();

  Entity* bulletManager = Entity::Instantiate("Bullet Manager");
  bulletManager->AddComponent<BulletManager>();

  // Tests
  Entity* networkEntity = Entity::Instantiate("Network Entity");
  networkEntity->AddComponent<NetworkMonitor>();

  EntityFactory::CreateDebugEntity();

  Input::RegisterKeyPressCallback(KeyCode::ESCAPE,
                                  []() { Application::Exit(); });

  GameManager::Instance().SendLevelLoadedMessage();
}

void Level1::BuildEnvironment() {
  Entity* ground{Entity::Instantiate("Ground")};
  ground->AddComponent<MeshComponent>("models/Ground/Level.scene.xml");
  ground->transform->SetWorldPos({0, -0.01f, 0});

  Entity* walls = Entity::Instantiate("Walls", nullptr, true);
  walls->transform->SetLocalScale(Math::Vector3{2});
  Entity* leftWall = Entity::Instantiate("Left Wall", walls, true);
  Entity* rightWall = Entity::Instantiate("Right Wall", walls, true);
  rightWall->SetTransform(Math::Vector3{-54, 0, 24}, Math::Vector3{0, 180, 0},
                          Math::Vector3::one);
  Entity* backWall = Entity::Instantiate("Back Wall", walls, true);
  backWall->SetTransform(Math::Vector3{-6, 0, 42}, Math::Vector3{0, -90, 0},
                         Math::Vector3::one);
  Entity* wall;
  /// Left Wall
  wall = Entity::Instantiate("Wall", leftWall, true);
  wall->transform->SetLocalPos(Math::Vector3{0, 0, 0});
  wall->AddComponent<MeshComponent>("MoreNature\\naturePack_119.scene.xml");
  //
  wall = Entity::Instantiate("Wall", leftWall, true);
  wall->transform->SetLocalPos(Math::Vector3{0, 0, 3});
  wall->AddComponent<MeshComponent>("MoreNature\\naturePack_119.scene.xml");
  //
  wall = Entity::Instantiate("Wall", leftWall, true);
  wall->transform->SetLocalPos(Math::Vector3{0, 0, 6});
  wall->AddComponent<MeshComponent>("MoreNature\\naturePack_119.scene.xml");
  //
  wall = Entity::Instantiate("Wall", leftWall, true);
  wall->transform->SetLocalPos(Math::Vector3{9, 0, 9});
  wall->AddComponent<MeshComponent>("MoreNature\\naturePack_119.scene.xml");
  //
  wall = Entity::Instantiate("Wall", leftWall, true);
  wall->transform->SetLocalPos(Math::Vector3{9, 0, 12});
  wall->AddComponent<MeshComponent>("MoreNature\\naturePack_119.scene.xml");
  //
  wall = Entity::Instantiate("Wall", leftWall, true);
  wall->transform->SetLocalPos(Math::Vector3{0, 0, 15});
  wall->AddComponent<MeshComponent>("MoreNature\\naturePack_119.scene.xml");
  //
  wall = Entity::Instantiate("Wall", leftWall, true);
  wall->transform->SetLocalPos(Math::Vector3{0, 0, 18});
  wall->AddComponent<MeshComponent>("MoreNature\\naturePack_119.scene.xml");
  //
  wall = Entity::Instantiate("Wall", leftWall, true);
  wall->transform->SetLocalPos(Math::Vector3{0, 0, 21});
  wall->AddComponent<MeshComponent>("MoreNature\\naturePack_119.scene.xml");
  //
  wall = Entity::Instantiate("Wall", leftWall, true);
  wall->transform->SetLocalPos(Math::Vector3{-12, 0, 24});
  wall->AddComponent<MeshComponent>("MoreNature\\naturePack_119.scene.xml");
  //
  wall = Entity::Instantiate("Wall", leftWall, true);
  wall->transform->SetLocalPos(Math::Vector3{-12, 0, 27});
  wall->AddComponent<MeshComponent>("MoreNature\\naturePack_119.scene.xml");
  //
  wall = Entity::Instantiate("Wall", leftWall, true);
  wall->transform->SetLocalPos(Math::Vector3{-12, 0, 30});
  wall->AddComponent<MeshComponent>("MoreNature\\naturePack_119.scene.xml");
  /// Right Wall
  wall = Entity::Instantiate("Wall", rightWall, true);
  wall->transform->SetLocalPos(Math::Vector3{0, 0, 0});
  wall->AddComponent<MeshComponent>("MoreNature\\naturePack_119.scene.xml");
  //
  wall = Entity::Instantiate("Wall", rightWall, true);
  wall->transform->SetLocalPos(Math::Vector3{0, 0, 3});
  wall->AddComponent<MeshComponent>("MoreNature\\naturePack_119.scene.xml");
  //
  wall = Entity::Instantiate("Wall", rightWall, true);
  wall->transform->SetLocalPos(Math::Vector3{0, 0, 6});
  wall->AddComponent<MeshComponent>("MoreNature\\naturePack_119.scene.xml");
  //
  wall = Entity::Instantiate("Wall", rightWall, true);
  wall->transform->SetLocalPos(Math::Vector3{0, 0, 9});
  wall->AddComponent<MeshComponent>("MoreNature\\naturePack_119.scene.xml");
  //
  wall = Entity::Instantiate("Wall", rightWall, true);
  wall->transform->SetLocalPos(Math::Vector3{0, 0, 12});
  wall->AddComponent<MeshComponent>("MoreNature\\naturePack_119.scene.xml");
  //
  wall = Entity::Instantiate("Wall", rightWall, true);
  wall->transform->SetLocalPos(Math::Vector3{0, 0, 15});
  wall->AddComponent<MeshComponent>("MoreNature\\naturePack_119.scene.xml");
  //
  wall = Entity::Instantiate("Wall", rightWall, true);
  wall->transform->SetLocalPos(Math::Vector3{6, 0, -3});
  wall->AddComponent<MeshComponent>("MoreNature\\naturePack_119.scene.xml");
  //
  wall = Entity::Instantiate("Wall", rightWall, true);
  wall->transform->SetLocalPos(Math::Vector3{6, 0, -6});
  wall->AddComponent<MeshComponent>("MoreNature\\naturePack_119.scene.xml");
  //
  wall = Entity::Instantiate("Wall", rightWall, true);
  wall->transform->SetLocalPos(Math::Vector3{6, 0, -9});
  wall->AddComponent<MeshComponent>("MoreNature\\naturePack_119.scene.xml");
  //
  wall = Entity::Instantiate("Wall", rightWall, true);
  wall->transform->SetLocalPos(Math::Vector3{-3, 0, -12});
  wall->AddComponent<MeshComponent>("MoreNature\\naturePack_119.scene.xml");
  //
  wall = Entity::Instantiate("Wall", rightWall, true);
  wall->transform->SetLocalPos(Math::Vector3{-3, 0, -15});
  wall->AddComponent<MeshComponent>("MoreNature\\naturePack_119.scene.xml");
  /// Back Wall
  wall = Entity::Instantiate("Wall", backWall, true);
  wall->transform->SetLocalPos(Math::Vector3{-9, 0, -9});
  wall->AddComponent<MeshComponent>("MoreNature\\naturePack_119.scene.xml");
  //
  wall = Entity::Instantiate("Wall", backWall, true);
  wall->transform->SetLocalPos(Math::Vector3{-9, 0, -6});
  wall->AddComponent<MeshComponent>("MoreNature\\naturePack_119.scene.xml");
  //
  wall = Entity::Instantiate("Wall", backWall, true);
  wall->transform->SetLocalPos(Math::Vector3{-9, 0, -3});
  wall->AddComponent<MeshComponent>("MoreNature\\naturePack_119.scene.xml");
  //
  wall = Entity::Instantiate("Wall", backWall, true);
  wall->transform->SetLocalPos(Math::Vector3{0, 0, 0});
  wall->AddComponent<MeshComponent>("MoreNature\\naturePack_119.scene.xml");
  //
  wall = Entity::Instantiate("Wall", backWall, true);
  wall->transform->SetLocalPos(Math::Vector3{0, 0, 3});
  wall->AddComponent<MeshComponent>("MoreNature\\naturePack_119.scene.xml");
  //
  wall = Entity::Instantiate("Wall", backWall, true);
  wall->transform->SetLocalPos(Math::Vector3{0, 0, 6});
  wall->AddComponent<MeshComponent>("MoreNature\\naturePack_119.scene.xml");
  //
  wall = Entity::Instantiate("Wall", backWall, true);
  wall->transform->SetLocalPos(Math::Vector3{0, 0, 9});
  wall->AddComponent<MeshComponent>("MoreNature\\naturePack_119.scene.xml");
  //
  wall = Entity::Instantiate("Wall", backWall, true);
  wall->transform->SetLocalPos(Math::Vector3{9, 0, 12});
  wall->AddComponent<MeshComponent>("MoreNature\\naturePack_119.scene.xml");
  //
  wall = Entity::Instantiate("Wall", backWall, true);
  wall->transform->SetLocalPos(Math::Vector3{9, 0, 15});
  wall->AddComponent<MeshComponent>("MoreNature\\naturePack_119.scene.xml");
  //
  wall = Entity::Instantiate("Wall", backWall, true);
  wall->transform->SetLocalPos(Math::Vector3{9, 0, 18});
  wall->AddComponent<MeshComponent>("MoreNature\\naturePack_119.scene.xml");
  //
  wall = Entity::Instantiate("Wall", backWall, true);
  wall->transform->SetLocalPos(Math::Vector3{9, 0, 21});
  wall->AddComponent<MeshComponent>("MoreNature\\naturePack_119.scene.xml");
  //
  wall = Entity::Instantiate("Wall", backWall, true);
  wall->transform->SetLocalPos(Math::Vector3{3, 0, 24});
  wall->AddComponent<MeshComponent>("MoreNature\\naturePack_119.scene.xml");
  //
  wall = Entity::Instantiate("Wall", backWall, true);
  wall->transform->SetLocalPos(Math::Vector3{3, 0, 27});
  wall->AddComponent<MeshComponent>("MoreNature\\naturePack_119.scene.xml");
  //
  wall = Entity::Instantiate("Wall", backWall, true);
  wall->transform->SetLocalPos(Math::Vector3{3, 0, 30});
  wall->AddComponent<MeshComponent>("MoreNature\\naturePack_119.scene.xml");

  // Colliders
  Entity* colliders = Entity::Instantiate("Colliders", nullptr, true);
  colliders->AddComponent<BoxCollider>(Math::Vector3{0, 3, 3},
                                       Math::Vector3{2.5f, 6, 18});
  colliders->AddComponent<BoxCollider>(Math::Vector3{9.25f, 3, 11},
                                       Math::Vector3{21, 6, 2.5f});
  colliders->AddComponent<BoxCollider>(Math::Vector3{0, 3, 32},
                                       Math::Vector3{2.5f, 6, 18});
  colliders->AddComponent<BoxCollider>(Math::Vector3{18, 3, 18},
                                       Math::Vector3{2.5f, 6, 15});
  colliders->AddComponent<BoxCollider>(Math::Vector3{9.25f, 3, 24},
                                       Math::Vector3{21, 6, 2.5f});
  colliders->AddComponent<BoxCollider>(Math::Vector3{-11, 3, 42},
                                       Math::Vector3{27, 6, 2.5f});
  colliders->AddComponent<BoxCollider>(Math::Vector3{-24, 3, 51},
                                       Math::Vector3{2.5f, 6, 21});
  colliders->AddComponent<BoxCollider>(Math::Vector3{-36, 3, 60},
                                       Math::Vector3{24, 6, 2.5f});
  colliders->AddComponent<BoxCollider>(Math::Vector3{-48, 3, 54},
                                       Math::Vector3{2.5f, 6, 12});
  colliders->AddComponent<BoxCollider>(Math::Vector3{-57, 3, 48},
                                       Math::Vector3{18, 6, 2.5f});
  colliders->AddComponent<BoxCollider>(Math::Vector3{-66, 3, 39},
                                       Math::Vector3{2.5f, 6, 21});
  colliders->AddComponent<BoxCollider>(Math::Vector3{-61, 3, 29},
                                       Math::Vector3{15, 6, 2.5f});
  colliders->AddComponent<BoxCollider>(Math::Vector3{-54, 3, 12},
                                       Math::Vector3{2.5f, 6, 36.5});
  colliders->AddComponent<BoxCollider>(Math::Vector3{-27, 3, -7},
                                       Math::Vector3{54, 6, 2.5f});
}
