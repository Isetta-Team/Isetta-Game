/*
 * Copyright (c) 2018 Isetta
 */
#include <IsettaEngine.h>

#include "Player/PlayerController.h"

#include "Gameplay/GameManager.h"
#include "Networking/PlayerMessages.h"
#include "Player/Bullet.h"
#include "Player/PlayerHealth.h"

void PlayerController::Awake() {
  RegisterNetworkCallbacks();
  entity->AddComponent<PlayerHealth>();
  // auto* mesh =
  //     entity->AddComponent<MeshComponent>("models/Player/Vanguard.scene.xml");
  auto* mesh =
      entity->AddComponent<MeshComponent>("Halves/Soldier/Soldier.scene.xml");
  animator = entity->AddComponent<AnimationComponent>(mesh);
  animator->AddAnimation("models/Player/Player_Idle.anim");
  // idleState = animator->AddAnimation("Halves/Soldier/Soldier_Idle.anim", 0,
  // "", false);
  animator->AddAnimation("models/Player/Player_Run.anim");
  animator->AddAnimation("models/Player/Player_Shoot.anim");
  // runShootState =
  // animator->AddAnimation("models/Player/Player_ShootRun.anim", 0, "", false);
  animator->AddAnimation("Halves/Soldier/Soldier.anim");
  animator->AddAnimation("models/Player/Player_Die.anim");
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
        CmdShoot();
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
      CmdChangeState(State::RunShoot);
    } else if (shouldRun) {
      transform->LookAt(transform->GetWorldPos() + movement);
      CmdChangeState(State::Run);
    } else if (shouldShoot) {
      transform->LookAt(transform->GetWorldPos() + shootDir);
      CmdChangeState(State::Shoot);
    } else {
      CmdChangeState(State::Idle);
    }
  }
}

void PlayerController::GuiUpdate() {
  if (!networkId->HasClientAuthority()) {
    return;
  }

  static bool isOpen = true;
  GUI::Window(
      RectTransform{
          {-200, 200, 500, 300}, GUI::Pivot::TopRight, GUI::Pivot::TopRight},
      "Players",
      [this]() {
        float y = 5, x = 5, height = 20, width = 250;
        for (PlayerController* player : GameManager::Instance().players) {
          GUI::Text(RectTransform{Math::Rect{x, y, width, height}},
                    player->entity->GetName());
          y += height;
        }
        GUI::SliderFloat(RectTransform{{x, y, width, height}}, "Move Speed    ",
                         &moveSpeed, 1, 15);
        y += height;
        GUI::SliderFloat(RectTransform{{x, y, width, height}}, "Shoot Interval",
                         &shootInterval, 0, 0.2);
        y += height;
        GUI::InputVector3(RectTransform{{x, y, width, height}},
                          "Bullet offset ", &bulletOffset);
        y += height;
        GUI::SliderFloat(RectTransform{{x, y, width, height}}, "Shoot Speed   ",
                         &shootSpeed, 10, 50);
      },
      &isOpen);
}

void PlayerController::ChangeState(int newState) {
  animator->TransitToAnimationState(newState, transitionDuration);
  state = static_cast<State>(newState);
}

void PlayerController::RegisterNetworkCallbacks() {
  static bool isShared = false;
  if (!isShared) {
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
          bullet->AddComponent<Bullet>()->Initialize(
              inMessage->startPos, inMessage->dir, inMessage->speed);
        });

    NetworkManager::Instance().RegisterServerCallback<PlayerStateChangeMessage>(
        [](int clientIndex, yojimbo::Message* inMessage) {
          NetworkManager::Instance()
              .SendMessageFromServerToAll<PlayerStateChangeMessage>(inMessage);
        });
    NetworkManager::Instance().RegisterClientCallback<PlayerStateChangeMessage>(
        [](yojimbo::Message* inMessage) {
          auto* message =
              reinterpret_cast<PlayerStateChangeMessage*>(inMessage);
          GameManager::Instance()
              .GetPlayer(message->playerIndex)
              ->ChangeState(message->newState);
        });
    isShared = true;
  }
}

void PlayerController::CmdShoot() {
  NetworkManager::Instance().SendMessageFromClient<ShootMessage>(
      [this](ShootMessage* message) {
        message->startPos = GetBulletPos();
        message->dir = transform->GetForward();
        message->speed = shootSpeed;
        message->playerNetId = networkId->id;
      });
}

void PlayerController::CmdChangeState(State state) const {
  if (this->state != state) {
    NetworkManager::Instance().SendMessageFromClient<PlayerStateChangeMessage>(
        [state](PlayerStateChangeMessage* message) {
          message->playerIndex = NetworkManager::Instance().GetClientIndex();
          message->newState = static_cast<int>(state);
        });
  }
}

Math::Vector3 PlayerController::GetBulletPos() const {
  return transform->WorldPosFromLocalPos(bulletOffset);
}
