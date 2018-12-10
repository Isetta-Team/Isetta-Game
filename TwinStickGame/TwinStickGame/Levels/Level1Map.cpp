/*
 * Copyright (c) 2018 Isetta
 */
#include "Level1Map.h"
#include <IsettaEngine.h>

#include <Components/Editor/EditorComponent.h>
#include <Components/FlyController.h>
#include <Components/GridComponent.h>
#include <Components/JointFollow.h>
#include <Scene/Layers.h>

#include "TestComponent.h"

void Level1Map::Load() {
  if (LevelManager::Instance().loadedLevel == this) {
    LoadTestEntities();
  }

  int environmentLayer = Layers::NewLayer("Environment");
  Collisions::SetIgnoreLayerCollision(environmentLayer, environmentLayer);

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
  wall->AddComponent<MeshComponent>(
      "models\\Environment\\naturePack_119.scene.xml");
  //
  wall = Entity::Instantiate("Wall", leftWall, true);
  wall->transform->SetLocalPos(Math::Vector3{0, 0, 3});
  wall->AddComponent<MeshComponent>(
      "models\\Environment\\naturePack_119.scene.xml");
  //
  wall = Entity::Instantiate("Wall", leftWall, true);
  wall->transform->SetLocalPos(Math::Vector3{0, 0, 6});
  wall->AddComponent<MeshComponent>(
      "models\\Environment\\naturePack_119.scene.xml");
  //
  wall = Entity::Instantiate("Wall", leftWall, true);
  wall->transform->SetLocalPos(Math::Vector3{9, 0, 9});
  wall->AddComponent<MeshComponent>(
      "models\\Environment\\naturePack_119.scene.xml");
  //
  wall = Entity::Instantiate("Wall", leftWall, true);
  wall->transform->SetLocalPos(Math::Vector3{9, 0, 12});
  wall->AddComponent<MeshComponent>(
      "models\\Environment\\naturePack_119.scene.xml");
  //
  wall = Entity::Instantiate("Wall", leftWall, true);
  wall->transform->SetLocalPos(Math::Vector3{0, 0, 15});
  wall->AddComponent<MeshComponent>(
      "models\\Environment\\naturePack_119.scene.xml");
  //
  wall = Entity::Instantiate("Wall", leftWall, true);
  wall->transform->SetLocalPos(Math::Vector3{0, 0, 18});
  wall->AddComponent<MeshComponent>(
      "models\\Environment\\naturePack_119.scene.xml");
  //
  wall = Entity::Instantiate("Wall", leftWall, true);
  wall->transform->SetLocalPos(Math::Vector3{0, 0, 21});
  wall->AddComponent<MeshComponent>(
      "models\\Environment\\naturePack_119.scene.xml");
  //
  wall = Entity::Instantiate("Wall", leftWall, true);
  wall->transform->SetLocalPos(Math::Vector3{-12, 0, 24});
  wall->AddComponent<MeshComponent>(
      "models\\Environment\\naturePack_119.scene.xml");
  //
  wall = Entity::Instantiate("Wall", leftWall, true);
  wall->transform->SetLocalPos(Math::Vector3{-12, 0, 27});
  wall->AddComponent<MeshComponent>(
      "models\\Environment\\naturePack_119.scene.xml");
  //
  wall = Entity::Instantiate("Wall", leftWall, true);
  wall->transform->SetLocalPos(Math::Vector3{-12, 0, 30});
  wall->AddComponent<MeshComponent>(
      "models\\Environment\\naturePack_119.scene.xml");
  /// Right Wall
  wall = Entity::Instantiate("Wall", rightWall, true);
  wall->transform->SetLocalPos(Math::Vector3{0, 0, 0});
  wall->AddComponent<MeshComponent>(
      "models\\Environment\\naturePack_119.scene.xml");
  //
  wall = Entity::Instantiate("Wall", rightWall, true);
  wall->transform->SetLocalPos(Math::Vector3{0, 0, 3});
  wall->AddComponent<MeshComponent>(
      "models\\Environment\\naturePack_119.scene.xml");
  //
  wall = Entity::Instantiate("Wall", rightWall, true);
  wall->transform->SetLocalPos(Math::Vector3{0, 0, 6});
  wall->AddComponent<MeshComponent>(
      "models\\Environment\\naturePack_119.scene.xml");
  //
  wall = Entity::Instantiate("Wall", rightWall, true);
  wall->transform->SetLocalPos(Math::Vector3{0, 0, 9});
  wall->AddComponent<MeshComponent>(
      "models\\Environment\\naturePack_119.scene.xml");
  //
  wall = Entity::Instantiate("Wall", rightWall, true);
  wall->transform->SetLocalPos(Math::Vector3{0, 0, 12});
  wall->AddComponent<MeshComponent>(
      "models\\Environment\\naturePack_119.scene.xml");
  //
  wall = Entity::Instantiate("Wall", rightWall, true);
  wall->transform->SetLocalPos(Math::Vector3{0, 0, 15});
  wall->AddComponent<MeshComponent>(
      "models\\Environment\\naturePack_119.scene.xml");
  //
  wall = Entity::Instantiate("Wall", rightWall, true);
  wall->transform->SetLocalPos(Math::Vector3{6, 0, -3});
  wall->AddComponent<MeshComponent>(
      "models\\Environment\\naturePack_119.scene.xml");
  //
  wall = Entity::Instantiate("Wall", rightWall, true);
  wall->transform->SetLocalPos(Math::Vector3{6, 0, -6});
  wall->AddComponent<MeshComponent>(
      "models\\Environment\\naturePack_119.scene.xml");
  //
  wall = Entity::Instantiate("Wall", rightWall, true);
  wall->transform->SetLocalPos(Math::Vector3{6, 0, -9});
  wall->AddComponent<MeshComponent>(
      "models\\Environment\\naturePack_119.scene.xml");
  //
  wall = Entity::Instantiate("Wall", rightWall, true);
  wall->transform->SetLocalPos(Math::Vector3{-3, 0, -12});
  wall->AddComponent<MeshComponent>(
      "models\\Environment\\naturePack_119.scene.xml");
  //
  wall = Entity::Instantiate("Wall", rightWall, true);
  wall->transform->SetLocalPos(Math::Vector3{-3, 0, -15});
  wall->AddComponent<MeshComponent>(
      "models\\Environment\\naturePack_119.scene.xml");
  /// Back Wall
  wall = Entity::Instantiate("Wall", backWall, true);
  wall->transform->SetLocalPos(Math::Vector3{-9, 0, -9});
  wall->AddComponent<MeshComponent>(
      "models\\Environment\\naturePack_119.scene.xml");
  //
  wall = Entity::Instantiate("Wall", backWall, true);
  wall->transform->SetLocalPos(Math::Vector3{-9, 0, -6});
  wall->AddComponent<MeshComponent>(
      "models\\Environment\\naturePack_119.scene.xml");
  //
  wall = Entity::Instantiate("Wall", backWall, true);
  wall->transform->SetLocalPos(Math::Vector3{-9, 0, -3});
  wall->AddComponent<MeshComponent>(
      "models\\Environment\\naturePack_119.scene.xml");
  //
  wall = Entity::Instantiate("Wall", backWall, true);
  wall->transform->SetLocalPos(Math::Vector3{0, 0, 0});
  wall->AddComponent<MeshComponent>(
      "models\\Environment\\naturePack_119.scene.xml");
  //
  wall = Entity::Instantiate("Wall", backWall, true);
  wall->transform->SetLocalPos(Math::Vector3{0, 0, 3});
  wall->AddComponent<MeshComponent>(
      "models\\Environment\\naturePack_119.scene.xml");
  //
  wall = Entity::Instantiate("Wall", backWall, true);
  wall->transform->SetLocalPos(Math::Vector3{0, 0, 6});
  wall->AddComponent<MeshComponent>(
      "models\\Environment\\naturePack_119.scene.xml");
  //
  wall = Entity::Instantiate("Wall", backWall, true);
  wall->transform->SetLocalPos(Math::Vector3{0, 0, 9});
  wall->AddComponent<MeshComponent>(
      "models\\Environment\\naturePack_119.scene.xml");
  //
  wall = Entity::Instantiate("Wall", backWall, true);
  wall->transform->SetLocalPos(Math::Vector3{9, 0, 12});
  wall->AddComponent<MeshComponent>(
      "models\\Environment\\naturePack_119.scene.xml");
  //
  wall = Entity::Instantiate("Wall", backWall, true);
  wall->transform->SetLocalPos(Math::Vector3{9, 0, 15});
  wall->AddComponent<MeshComponent>(
      "models\\Environment\\naturePack_119.scene.xml");
  //
  wall = Entity::Instantiate("Wall", backWall, true);
  wall->transform->SetLocalPos(Math::Vector3{9, 0, 18});
  wall->AddComponent<MeshComponent>(
      "models\\Environment\\naturePack_119.scene.xml");
  //
  wall = Entity::Instantiate("Wall", backWall, true);
  wall->transform->SetLocalPos(Math::Vector3{9, 0, 21});
  wall->AddComponent<MeshComponent>(
      "models\\Environment\\naturePack_119.scene.xml");
  //
  wall = Entity::Instantiate("Wall", backWall, true);
  wall->transform->SetLocalPos(Math::Vector3{3, 0, 24});
  wall->AddComponent<MeshComponent>(
      "models\\Environment\\naturePack_119.scene.xml");
  //
  wall = Entity::Instantiate("Wall", backWall, true);
  wall->transform->SetLocalPos(Math::Vector3{3, 0, 27});
  wall->AddComponent<MeshComponent>(
      "models\\Environment\\naturePack_119.scene.xml");
  //
  wall = Entity::Instantiate("Wall", backWall, true);
  wall->transform->SetLocalPos(Math::Vector3{3, 0, 30});
  wall->AddComponent<MeshComponent>(
      "models\\Environment\\naturePack_119.scene.xml");

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

  // Floor
  float floorHeight = -0.5;
  Entity* leftFloor = Entity::Instantiate("Left Floor", nullptr, true);
  leftFloor->SetTransform(Math::Vector3{0, floorHeight, 24}, Math::Vector3{},
                          Math::Vector3{6, 1, 4});
  leftFloor->AddComponent<MeshComponent>(
      "models\\Environment\\naturePack_001.scene.xml");
  Entity* mainFloor = Entity::Instantiate("Right Floor", nullptr, true);
  mainFloor->SetTransform(Math::Vector3{-54, floorHeight, 42}, Math::Vector3{},
                          Math::Vector3{18, 1, 16});
  mainFloor->AddComponent<MeshComponent>(
      "models\\Environment\\naturePack_001.scene.xml");
  Entity* rightFloor = Entity::Instantiate("Main Floor", nullptr, true);
  rightFloor->SetTransform(Math::Vector3{-66, floorHeight, 48}, Math::Vector3{},
                           Math::Vector3{4, 1, 6});
  rightFloor->AddComponent<MeshComponent>(
      "models\\Environment\\naturePack_001.scene.xml");
  Entity* topFloor = Entity::Instantiate("Top Floor", nullptr, true);
  topFloor->SetTransform(Math::Vector3{-48, floorHeight, 60}, Math::Vector3{},
                         Math::Vector3{8, 1, 6});
  topFloor->AddComponent<MeshComponent>(
      "models\\Environment\\naturePack_001.scene.xml");
  Entity* fillerFloor = Entity::Instantiate("Filler Floor", nullptr, true);
  fillerFloor->SetTransform(Math::Vector3{-54, 0, 48}, Math::Vector3{},
                            Math::Vector3{2, 1, 2});
  fillerFloor->AddComponent<MeshComponent>(
      "models\\Environment\\naturePack_001.scene.xml");

  // Obstacles
  struct RockGroup {
    Math::Vector2 position;
    RockGroup(const Math::Vector2& position) : position{position} {
      Entity* rockGroup = Entity::Instantiate("Rock Group", nullptr, true);
      rockGroup->SetTransform(Math::Vector3{position.x, 0, position.y},
                              Math::Vector3::zero, Math::Vector3{2});
      rockGroup->AddComponent<BoxCollider>(Math::Vector3{1.6f, 0, -1.1f},
                                           Math::Vector3{2.3f, 1, 2.5f});

      Entity* vertRock = Entity::Instantiate("Vertical Rock", rockGroup, true);
      vertRock->transform->SetLocalPos(Math::Vector3{-0.24f, 0, 0.353f});
      vertRock->AddComponent<MeshComponent>(
          "models\\Environment\\naturePack_018.scene.xml");
      Entity* bigRock = Entity::Instantiate("Big Rock", rockGroup, true);
      bigRock->AddComponent<MeshComponent>(
          "models\\Environment\\naturePack_016.scene.xml");
      Entity* lilRock = Entity::Instantiate("Little Rock", rockGroup, true);
      lilRock->transform->SetLocalPos(Math::Vector3{1.575f, 0.118f, 0.756f});
      lilRock->transform->RotateLocal(159.659f * Math::Vector3::up);
      lilRock->AddComponent<MeshComponent>(
          "models\\Environment\\naturePack_021.scene.xml");
    }

    Nav2DObstacle GetObstacle() const {
      return Nav2DObstacle::Rectangle(Math::Rect{
          position + Math::Vector2{-0.7f, 1.5f}, Math::Vector2{4.5f, -5.2}});
    }
  };

  RockGroup group1{Math::Vector2{-16.75f, 5.56f}};
  RockGroup group2{Math::Vector2{-37.6f, 21.3f}};
  RockGroup group3{Math::Vector2{14.8f, 13.08f}};
  Entity* crater1 = Entity::Instantiate("Crater", nullptr, true);
  crater1->SetTransform(Math::Vector3{-16.96f, 0.23f, 28.36f},
                        Math::Vector3::zero, Math::Vector3{3, 2, 3});
  crater1->AddComponent<MeshComponent>(
      "models\\Environment\\naturePack_079.scene.xml");
  crater1->AddComponent<SphereCollider>(Math::Vector3{1.4f, 0, -1.5f}, 0.65f);
  Entity* crater2 = Entity::Instantiate("Crater", nullptr, true);
  crater2->SetTransform(Math::Vector3{-38.13, 0.23f, 11.94f},
                        Math::Vector3::zero, Math::Vector3{3, 2, 3});
  crater2->AddComponent<MeshComponent>(
      "models\\Environment\\naturePack_079.scene.xml");
  crater2->AddComponent<SphereCollider>(Math::Vector3{1.4f, 0, -1.5f}, 0.65f);
  Entity* mountain = Entity::Instantiate("Mountain", nullptr, true);
  mountain->SetTransform(Math::Vector3{-50, 0, 62.9f}, Math::Vector3::zero,
                         Math::Vector3{5});
  mountain->AddComponent<MeshComponent>(
      "models\\Environment\\naturePack_032.scene.xml");
  mountain->AddComponent<BoxCollider>(Math::Vector3{9, 2, -5.2f},
                                      Math::Vector3{0.5f, 1, 2});
  mountain->AddComponent<BoxCollider>(Math::Vector3{4, 2, -9},
                                      Math::Vector3{2, 1, 0.5f});
  Entity* pillar = Entity::Instantiate("Pillar", nullptr, true);
  pillar->SetTransform(Math::Vector3{-24.82f, 0, 44.17f},
                       Math::Vector3{0, 27.5f, 0}, Math::Vector3{3});
  pillar->AddComponent<MeshComponent>(
      "models\\Environment\\naturePack_133.scene.xml");
  pillar->AddComponent<CapsuleCollider>(Math::Vector3{0.5f, 1.5, -2.9f}, 0.75f,
                                        3);

  // AI Plane
  navPlane =
      Nav2DPlane{Math::Rect{-75, -25, 100, 100}, Math::Vector2Int{25, 25}};
  navPlane.AddObstacle(Nav2DObstacle(
      {{-53.f, -7.f}, {-1.f, -7.f}, {-1, 10},  {17, 10},  {17, 23},  {-1, 23},
       {-1, 24},      {-1, 25},     {-1, 26},  {-1, 30},  {-1, 41},  {-25, 41},
       {-25, 59},     {-30, 59},    {-44, 59}, {-45, 59}, {-46, 59}, {-48, 59},
       {-48, 47},     {-65, 47},    {-65, 30}, {-53, 30}, {-53, -7}}));
  navPlane.AddObstacle(group1.GetObstacle());
  navPlane.AddObstacle(group2.GetObstacle());
  navPlane.AddObstacle(group3.GetObstacle());
  navPlane.AddObstacle(Nav2DObstacle::Circle(
      Math::Vector2{crater1->transform->GetWorldPos().x + 1.35f,
                    crater1->transform->GetWorldPos().z - 1.5f},
      2, 6));
  navPlane.AddObstacle(Nav2DObstacle::Circle(
      Math::Vector2{crater2->transform->GetWorldPos().x + 1.35f,
                    crater2->transform->GetWorldPos().z - 1.5f},
      2, 6));
}

void Level1Map::LoadTestEntities() {
  Entity* camera = Entity::Instantiate("Camera");
  camera->AddComponent<CameraComponent>();
  camera->transform->SetWorldPos({15, 15, 30});
  camera->transform->LookAt(Math::Vector3::zero);
  camera->AddComponent<FlyController>();

  Entity* light = Entity::Instantiate("Light");
  light->AddComponent<LightComponent>();
  light->SetTransform(Math::Vector3{0, 200, 600}, Math::Vector3::zero,
                      Math::Vector3::one);
  // light->SetProperty<LightComponent::Property::COLOR>(Color{1, 1, 1});
  // light->SetProperty<LightComponent::Property::FOV>(360);
  // light->SetProperty<LightComponent::Property::RADIUS>(30);
  // light->SetProperty<LightComponent::Property::RADIUS>(2500);

  Entity* debug = Entity::Instantiate("Debug", nullptr, true);
  // debug->AddComponent<GridComponent>();
  debug->AddComponent<EditorComponent>();

  Entity* test = Entity::Instantiate("test");
  test->AddComponent<TestComponent>(&navPlane);
  // Entity* testAgent = Entity::Instantiate("Agent");
  // auto agentComp = testAgent->AddComponent<Nav2DAgent>(&testComp->plane);
  // navPlane.AddTarget(testAgent->transform);

  // Characters
  Entity* player = Entity::Instantiate("Player");
  player->transform->SetWorldPos(Math::Vector3{-5, 0, 4});
  auto playerMesh =
      player->AddComponent<MeshComponent>("models\\Soldier\\idle.scene.xml");
  auto playerAnim = player->AddComponent<AnimationComponent>(playerMesh);
  playerAnim->AddAnimation("models\\Soldier\\idle.anim");
  playerAnim->AddAnimation("models\\Soldier\\impact.anim");
  playerAnim->AddAnimation("models\\Soldier\\walking.anim");
  playerAnim->AddAnimation("models\\Soldier\\death.anim");

  Entity* weapon = Entity::Instantiate("Weapon");
  weapon->transform->SetLocalScale(Math::Vector3{0.75f});
  weapon->AddComponent<MeshComponent>(
      "models\\Weapons\\flamethrower.scene.xml");
  // weapon->AddComponent<JointFollow>(playerMesh, "mixamorig_LeftHand",
  //                                  Math::Vector3{-0.1f, 0.05f, 0.05f},
  //                                  Math::Vector3{-5, 55, 180});
  weapon->AddComponent<JointFollow>(playerMesh, "mixamorig_RightHand",
                                    Math::Vector3{0.1f, 0, 0.4f},
                                    Math::Vector3{0, 180, 100});

  static int playerState = 0;
  Input::RegisterKeyPressCallback(KeyCode::N, [playerAnim]() {
    if (playerState == 4) playerState = 0;
    playerAnim->TransitToAnimationState(playerState++, 0.2);
  });

  Entity* enemy = Entity::Instantiate("Enemy");
  enemy->transform->SetWorldPos(Math::Vector3{-10, 0, 4});
  auto enemyMesh =
      enemy->AddComponent<MeshComponent>("models\\Enemy\\running.scene.xml");
  auto enemyAnim = enemy->AddComponent<AnimationComponent>(enemyMesh);
  enemyAnim->AddAnimation("models\\Enemy\\running.anim");
  enemyAnim->AddAnimation("models\\Enemy\\punching.anim");
  enemyAnim->AddAnimation("models\\Enemy\\death.anim");

  static int enemyState = 0;
  Input::RegisterKeyPressCallback(KeyCode::M, [enemyAnim]() {
    if (enemyState == 3) enemyState = 0;
    enemyAnim->TransitToAnimationState(enemyState++, 0.2);
  });
}
