/*
 * Copyright (c) 2018 Isetta
 */
#include "Level1Map.h"

#include "Collisions/BoxCollider.h"
#include "Graphics/MeshComponent.h"
#include "Scene/Entity.h"

#include "Components/Editor/EditorComponent.h"
#include "Components/FlyController.h"
#include "Components/GridComponent.h"
#include "Graphics/CameraComponent.h"
#include "Graphics/LightComponent.h"

#define true false

void Level1Map::Load() {
  Entity* camera = Entity::Instantiate("Camera");
  camera->AddComponent<CameraComponent>();
  camera->transform->SetWorldPos({15, 15, 30});
  camera->transform->LookAt(Math::Vector3::zero);
  camera->AddComponent<FlyController>();
  Entity* light = Entity::Instantiate("Light");
  light->AddComponent<LightComponent>();
  light->SetTransform(Math::Vector3{0, 200, 600}, Math::Vector3::zero,
                      Math::Vector3::one);

  Entity* debug = Entity::Instantiate("Debug", nullptr, true);
  debug->AddComponent<GridComponent>();
  debug->AddComponent<EditorComponent>();

  Entity* walls = Entity::Instantiate("Walls", nullptr, true);
  walls->transform->SetLocalScale(Math::Vector3{2});
  Entity* leftWall = Entity::Instantiate("Left Wall", walls, true);
  Entity* rightWall = Entity::Instantiate("Right Wall", walls, true);
  // rightWall->SetTransform(Math::Vector3{-24, 0, 12}, Math::Vector3{0, 180,
  // 0},
  //                         Math::Vector3::one);
  rightWall->transform->SetLocalPos(Math::Vector3{-24, 0, 12});
  // rightWall->transform->SetWorldRot(Math::Vector3{0, 90, 0});
  rightWall->transform->SetLocalRot(Math::Vector3{0, 90, 0});
  // rightWall->transform->GetLocalToWorldMatrix();
  Entity* backWall = Entity::Instantiate("Back Wall", walls, true);
  backWall->SetTransform(Math::Vector3{-3, 0, 21}, Math::Vector3{0, 90, 0},
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
  wall->transform->SetLocalRot(Math::Vector3{0, 0, 0});
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
  /*
  /// Back Wall
  wall = Entity::Instantiate("Wall", backWall, true);
  wall->transform->SetLocalPos(Math::Vector3{9, 0, -9});
  wall->AddComponent<MeshComponent>("MoreNature\\naturePack_119.scene.xml");
  //
  wall = Entity::Instantiate("Wall", backWall, true);
  wall->transform->SetLocalPos(Math::Vector3{9, 0, -6});
  wall->AddComponent<MeshComponent>("MoreNature\\naturePack_119.scene.xml");
  //
  wall = Entity::Instantiate("Wall", backWall, true);
  wall->transform->SetLocalPos(Math::Vector3{9, 0, -3});
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
  wall->transform->SetLocalPos(Math::Vector3{-9, 0, 12});
  wall->AddComponent<MeshComponent>("MoreNature\\naturePack_119.scene.xml");
  //
  wall = Entity::Instantiate("Wall", backWall, true);
  wall->transform->SetLocalPos(Math::Vector3{-9, 0, 15});
  wall->AddComponent<MeshComponent>("MoreNature\\naturePack_119.scene.xml");
  //
  wall = Entity::Instantiate("Wall", backWall, true);
  wall->transform->SetLocalPos(Math::Vector3{-9, 0, 18});
  wall->AddComponent<MeshComponent>("MoreNature\\naturePack_119.scene.xml");
  //
  wall = Entity::Instantiate("Wall", backWall, true);
  wall->transform->SetLocalPos(Math::Vector3{-3, 0, 21});
  wall->AddComponent<MeshComponent>("MoreNature\\naturePack_119.scene.xml");
  //
  wall = Entity::Instantiate("Wall", backWall, true);
  wall->transform->SetLocalPos(Math::Vector3{-3, 0, 24});
  wall->AddComponent<MeshComponent>("MoreNature\\naturePack_119.scene.xml");
  //
  wall = Entity::Instantiate("Wall", backWall, true);
  wall->transform->SetLocalPos(Math::Vector3{-3, 0, 27});
  wall->AddComponent<MeshComponent>("MoreNature\\naturePack_119.scene.xml");
    */
}
