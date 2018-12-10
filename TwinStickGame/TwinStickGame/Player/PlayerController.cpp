/*
 * Copyright (c) 2018 Isetta
 */
#include <IsettaEngine.h>

#include <Components/JointFollow.h>
#include "Consts.h"
#include "Enemy/EnemyManager.h"
#include "Gameplay/Damageable.h"
#include "Gameplay/GameManager.h"
#include "Networking/NetworkMessages.h"
#include "Player/PlayerController.h"

void PlayerController::Awake() {
  RegisterNetworkCallbacks();
  auto* damageable = entity->AddComponent<Damageable>(100.f);

  audioComp = entity->AddComponent<AudioSource>();
  audioComp->SetProperty(AudioSource::Property::IS_3D, false);
  audioComp->SetProperty(AudioSource::Property::LOOP, false);
  playerDamage = AudioClip::Load("audio/player_hit.wav");
  playerDie = AudioClip::Load("audio/die.wav");

  damageable->damageDelegate.Subscribe([this](int playerIndex) {
    audioComp->clip = playerDamage;
    audioComp->SetVolume(1.0f);
    audioComp->Play();
  });

  auto* mesh =
      entity->AddComponent<MeshComponent>("models/Player/Vanguard.scene.xml");
  animator = entity->AddComponent<AnimationComponent>(mesh);
  animator->AddAnimation("models/Player/Player_Idle.anim");
  animator->AddAnimation("models/Player/Player_Run.anim");
  animator->AddAnimation("models/Player/Player_Shoot.anim");
  animator->AddAnimation("models/Player/Player_ShootRun.anim");
  animator->AddAnimation("models/Player/Player_Die.anim");

  weapon = Entity::Instantiate("Weapon");
  weapon->transform->SetLocalScale(Math::Vector3{0.75f});
  weapon->AddComponent<MeshComponent>(
      "models\\Weapons\\flamethrower.scene.xml");
  weapon->AddComponent<JointFollow>(mesh, "mixamorig_LeftHand",
                                    Math::Vector3{-0.1f, 0.05f, 0.05f},
                                    Math::Vector3::zero);

  // called on each client automatically as health is synced
  damageable->onDeath.Subscribe([this](int playerIndex) {
    ChangeState(static_cast<int>(State::Die));
    isAlive = false;
    if (NetworkManager::Instance().IsHost()) {
      GameManager::Instance().NotifyPlayerDied(this->playerIndex);
      EnemyManager::Instance().RemoveTarget(transform);
    }

    weapon->SetActive(false);

    audioComp->clip = playerDie;
    audioComp->SetVolume(2.0f);
    audioComp->Play();
  });
}

void PlayerController::Start() {
  networkId = entity->GetComponent<NetworkId>();
}

void PlayerController::Update() {
  if (networkId->HasClientAuthority() && isAlive) {
    float dt = Time::GetDeltaTime();

    Math::Vector3 movement(-Input::GetGamepadAxis(GamepadAxis::L_HORIZONTAL), 0,
                           -Input::GetGamepadAxis(GamepadAxis::L_VERTICAL));
    bool shouldRun = movement.Magnitude() > 0.2f;
    if (movement.Magnitude() > 1.f) movement.Normalize();

    Math::Vector3 shootDir =
        Math::Vector3(-Input::GetGamepadAxis(GamepadAxis::R_HORIZONTAL), 0,
                      -Input::GetGamepadAxis(GamepadAxis::R_VERTICAL));
    bool shouldShoot = shootDir.Magnitude() >= 1.f;

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

    // Translation
    if (shouldRun) {
      transform->TranslateWorld(movement * moveSpeed * dt);
    }

    // Shoot
    if (shouldShoot) {
      shootDir.Normalize();

      // Shoot countdown
      if (shootCooldown < 0.f) {
        CmdShoot();
        shootCooldown += shootInterval;
      }
      shootCooldown -= Time::GetDeltaTime();

      // DebugDraw::Line(transform->GetWorldPos(),
      //                 transform->GetWorldPos() + shootDir, Color::blue);
    } else {
      shootCooldown = 0.f;
    }
  }

  if (state == State::Die) {
    stateElapsed += 1;
    if (stateElapsed >= dieAnimationDuration && !isAnimationStopped) {
      animator->Stop();
      isAnimationStopped = true;
    }
  }
}

void PlayerController::GuiUpdate() {
  if (!networkId->HasClientAuthority()) {
    return;
  }
  RectTransform killsRect{
      {-20, 45, 0, 0}, GUI::Pivot::TopRight, GUI::Pivot::Right};
  GUI::Text(killsRect, Util::StrFormat("Kills: %0*d", 3, GetScore()),
            GUI::TextStyle{Consts::MID_SIZE, "Deathe"});

  GameManager::Instance().DrawGameOver();

  // static bool isOpen = true;
  // GUI::Window(
  //     RectTransform{
  //         {-100, 100, 500, 200}, GUI::Pivot::TopRight, GUI::Pivot::TopRight},
  //     "Players",
  //     [this]() {
  //       float y = 5, x = 5, height = 20, width = 250;
  //       for (PlayerController* player : GameManager::Instance().players) {
  //         if (player == nullptr) continue;
  //         GUI::Text(
  //             RectTransform{Math::Rect{x, y, width, height}},
  //             Util::StrFormat("%s \t %.0f",
  //             player->entity->GetName().c_str(),
  //                             player->score));
  //         y += height;
  //       }
  //       GUI::SliderFloat(RectTransform{{x, y, width, height}}, "Move Speed ",
  //                        &moveSpeed, 1, 15);
  //       y += height;
  //       GUI::SliderFloat(RectTransform{{x, y, width, height}}, "Shoot
  //       Interval",
  //                        &shootInterval, 0, 0.2);
  //       y += height;
  //       GUI::InputVector3(RectTransform{{x, y, width, height}},
  //                         "Bullet offset ", &bulletOffset);
  //       y += height;
  //       GUI::SliderFloat(RectTransform{{x, y, width, height}}, "Shoot Speed
  //       ",
  //                        &shootSpeed, 10, 50);
  //     },
  //     &isOpen);
}

void PlayerController::ChangeState(int newState) {
  animator->Play();
  isAnimationStopped = false;
  animator->TransitToAnimationState(newState, transitionDuration);
  state = static_cast<State>(newState);
  stateElapsed = 0.f;
}

void PlayerController::Score(const float score) { this->score += score; }

void PlayerController::RegisterNetworkCallbacks() {
  static bool areSharedCallbacksInitialized = false;
  if (!areSharedCallbacksInitialized) {
    // Animation
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
    areSharedCallbacksInitialized = true;
  }
}

void PlayerController::CmdShoot() {
  NetworkManager::Instance().SendMessageFromClient<ShootMessage>(
      [this](ShootMessage* message) {
        message->startPos = GetBulletPos();
        message->dir = transform->GetForward();
        message->speed = shootSpeed;
        message->range = bulletRange;
        message->damage = bulletDamage;
        message->playerIndex = playerIndex;
      });
}

void PlayerController::CmdChangeState(State newState) const {
  if (state != newState) {
    NetworkManager::Instance().SendMessageFromClient<PlayerStateChangeMessage>(
        [newState, this](PlayerStateChangeMessage* message) {
          message->playerIndex = playerIndex;
          message->newState = static_cast<int>(newState);
        });
  }
}

Math::Vector3 PlayerController::GetBulletPos() const {
  return transform->WorldPosFromLocalPos(bulletOffset);
}
