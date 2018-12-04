/*
 * Copyright (c) 2018 Isetta
 */
#include "Player/PlayerController.h"

#include <Core/IsettaCore.h>
#include <Networking/NetworkId.h>

#include "Networking/PlayerMessages.h"
#include "Player/Bullet.h"
#include "Player/PlayerHealth.h"

void PlayerController::Awake() {
  RegisterNetworkCallbacks();
  entity->AddComponent<PlayerHealth>();
  auto* mesh =
      entity->AddComponent<MeshComponent>("models/Player/Vanguard.scene.xml");
  animator = entity->AddComponent<AnimationComponent>(mesh);
  idleState =
      animator->AddAnimation("models/Player/Player_Idle.anim", 0, "", false);
  // idleState = animator->AddAnimation("Halves/Soldier/Soldier_Idle.anim", 0,
  // "", false);
  runState =
      animator->AddAnimation("models/Player/Player_Run.anim", 0, "", false);
  shootState =
      animator->AddAnimation("models/Player/Player_Shoot.anim", 0, "", false);
  // runShootState = animator->AddAnimation("models/Player/Player_ShootRun.anim",
                                         // 0, "", false);
  runShootState = animator->AddAnimation("Halves/Soldier/Soldier.anim", 0,
  "", false);
  dieState =
      animator->AddAnimation("models/Player/Player_Die.anim", 0, "", false);
}

void PlayerController::Start() {
  networkId = entity->GetComponent<NetworkId>();
}

void PlayerController::Update() {
  if (networkId->HasClientAuthority()) {
    float dt = Time::GetDeltaTime();

    Math::Vector3 movement(Input::GetGamepadAxis(GamepadAxis::L_HORIZONTAL), 0,
                           Input::GetGamepadAxis(GamepadAxis::L_VERTICAL));
    bool shouldRun = movement.Magnitude() > 0.2f;
    if (movement.Magnitude() > 1.f) movement.Normalize();

    Math::Vector3 shootDir =
        Math::Vector3(Input::GetGamepadAxis(GamepadAxis::R_HORIZONTAL), 0,
                      Input::GetGamepadAxis(GamepadAxis::R_VERTICAL));
    bool shouldShoot = shootDir.Magnitude() >= 1.f;

    // Translation
    if (shouldRun) {
      transform->TranslateWorld(movement * moveSpeed * dt);
    }

    // Shoot
    if (shouldShoot) {
      shootDir.Normalize();

      // Shoot countdown
      if (shootCooldown <= 0.f) {
        Shoot();
        shootCooldown += shootInterval;
      }
      shootCooldown -= Time::GetDeltaTime();

      DebugDraw::Line(transform->GetWorldPos(),
                      transform->GetWorldPos() + shootDir, Color::blue);
    } else {
      shootCooldown = 0.f;
    }

    // Animation & Look Dir
    if (shouldShoot && shouldRun) {
      transform->LookAt(transform->GetWorldPos() + shootDir);
      if (state != State::RunShoot) {
        animator->TransitToAnimationState(runShootState, transitionDuration);
        state = State::RunShoot;
      }
    } else if (shouldRun) {
      transform->LookAt(transform->GetWorldPos() + movement);
      if (state != State::Run) {
        animator->TransitToAnimationState(runState, transitionDuration);
        state = State::Run;
      }
    } else if (shouldShoot) {
      transform->LookAt(transform->GetWorldPos() + shootDir);
      if (state != State::Shoot) {
        animator->TransitToAnimationState(shootState, transitionDuration);
        state = State::Shoot;
      }
    } else {
      if (state != State::Idle) {
        animator->TransitToAnimationState(idleState, transitionDuration);
        state = State::Idle;
      }
    }
  }
}

void PlayerController::RegisterNetworkCallbacks() {
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
