/*
 * Copyright (c) 2018 Isetta
 */
#include "Player/PlayerController.h"

#include <Core/IsettaCore.h>
#include <Networking/NetworkId.h>

#include "Bullet.h"
#include "Gameplay/InputManager.h"
#include "Networking/PlayerMessages.h"

void PlayerController::Awake() {
  static bool registered = false;
  if (!registered) {
    NetworkManager::Instance().RegisterServerCallback<ShootMessage>(
        [](int clientIndex, yojimbo::Message* message) {
          NetworkManager::Instance().SendMessageFromServerToAll<ShootMessage>(
              message);
          // TODO(YIDI): hit scan
        });
    NetworkManager::Instance().RegisterClientCallback<ShootMessage>(
        [](yojimbo::Message* message) {
          auto* inMessage = reinterpret_cast<ShootMessage*>(message);
          auto* bullet = Entity::Instantiate("Bullet");
          bullet->AddComponent<MeshComponent>("models/Bullet/Bullet.scene.xml");
          bullet->AddComponent<Bullet>()->Initialize(inMessage->startPos,
                                                     inMessage->dir);
        });
    registered = true;
  }
}

void PlayerController::Start() {
  networkId = entity->GetComponent<NetworkId>();
}

void PlayerController::Update() {
  DebugDraw::WireCapsule(transform->GetLocalToWorldMatrix(), 0.5f, 2.f,
                         Color::green);

  if (networkId->HasClientAuthority()) {
    float dt = Time::GetDeltaTime();

    Math::Vector3 movement{InputManager::GetMovementInput().x, 0,
                           InputManager::GetMovementInput().y};

    if (movement.Magnitude() > 1) {
      movement.Normalize();
    }

    if (movement.Magnitude() > 0) {
      if (!isMoving) {
        isMoving = true;
      }
      transform->TranslateWorld(movement * moveSpeed * dt);
    } else {
      if (isMoving) {
        isMoving = false;
      }
    }

    Math::Vector3 lookDir{InputManager::GetShootInput().x, 0,
                          InputManager::GetShootInput().y};
    DebugDraw::Line(transform->GetWorldPos(), transform->GetWorldPos() + lookDir, Color::blue);

    if (lookDir.Magnitude() >= 1.f) {
      lookDir.Normalize();
      transform->LookAt(transform->GetWorldPos() + lookDir);

      if (shootCooldown <= 0.f) {
        Shoot();
        shootCooldown += shootInterval;
      }
      shootCooldown -= Time::GetDeltaTime();
    } else {
      shootCooldown = 0.f;
    }
  }
}

void PlayerController::Shoot() {
  NetworkManager::Instance().SendMessageFromClient<ShootMessage>(
      [this](ShootMessage* message) {
        message->startPos = GetBulletPos();
        message->dir = transform->GetForward();
        message->playerNetId = networkId->id;
      });
}

Math::Vector3 PlayerController::GetBulletPos() {
  return transform->GetWorldPos() + Math::Vector3::up * 0.5f;
}
