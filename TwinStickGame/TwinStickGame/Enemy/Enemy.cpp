/*
 * Copyright (c) 2018 Isetta
 */
#include <IsettaEngine.h>

#include "Enemy/Enemy.h"
#include "Gameplay/Damageable.h"
#include "Networking/NetworkMessages.h"
#include "Player/PlayerController.h"

using namespace Isetta;

void Enemy::Awake() {
  collider = entity->AddComponent<BoxCollider>();
  entity->SetLayer("Enemy");
  // collider->center = transform->GetLocalScale().y * Math::Vector3::up;
  collider->size = Math::Vector3{1, 20, 1};

  audioComp = entity->AddComponent<AudioSource>();
  audioComp->SetProperty(AudioSource::Property::IS_3D, false);
  audioComp->SetProperty(AudioSource::Property::LOOP, false);
  enemyDamage = AudioClip::Load("audio/enemy_damage.wav");

  damageable = entity->AddComponent<Damageable>(100);
  damageable->damageDelegate.Subscribe([this](int playerIndex) {
    audioComp->SetVolume(0.8f);
    audioComp->clip = enemyDamage;
    audioComp->Play();
    // if (particles != nullptr) Destroy(particles);
    // particles = entity->AddComponent<ParticleSystemComponent>();
  });
  // health is synced by HitEnemyMessage
  damageable->onDeath.Subscribe([this](int playerIndex) {
    if (NetworkManager::Instance().IsHost()) {
      NetworkManager::Instance().SendMessageFromServerToAll<ScoreMessage>(
          [this, playerIndex](ScoreMessage* message) {
            message->score = score;
            message->playerIndex = playerIndex;
          });
    }
    Die();
  });

  auto* mesh =
      entity->AddComponent<MeshComponent>("models/Enemy/running.scene.xml");
  animator = entity->AddComponent<AnimationComponent>(mesh);
  animator->AddAnimation("models/Enemy/running.anim");
  animator->AddAnimation("models/Enemy/punching.anim");
  animator->AddAnimation("models/Enemy/death.anim");
}

void Enemy::Update() {
  // put state management on server only
  switch (state) {
    case State::Run:
      if (NetworkManager::Instance().IsHost()) {
        Math::Vector3 targetPos{transform->GetWorldPos()};
        auto dir = agent->GetAIMovement({targetPos.x, targetPos.z},
                                        Time::GetDeltaTime());
        targetPos.x += dir.x * Time::GetDeltaTime() * speed;
        targetPos.z += dir.y * Time::GetDeltaTime() * speed;
        targetPos.y = 0;
        if ((targetPos - transform->GetWorldPos()).Magnitude() > Math::Util::EPSILON) {
          transform->LookAt(targetPos);
        }
        transform->SetWorldPos(targetPos);
      }
      break;

    case State::Punch:
      stateElapsed += Time::GetDeltaTime();
      if (stateElapsed >= punchAnimationDuration) {
        ChangeState(static_cast<int>(State::Run));
      }
      break;

    case State::Die:
      stateElapsed += Time::GetDeltaTime();
      if (stateElapsed > dieAnimationDuration) {
        entity->SetActive(false);
      }
      break;

    default:
      break;
  }
}

void Enemy::Reanimate() {
  state = State::Run;
  animator->TransitToAnimationState(static_cast<int>(state), 0.01f);
  damageable->Reset();
  collider->SetActive(true);
  // TODO(YIDI): Add respawn sound if any
}

void Enemy::Die() {
  // TODO(YIDI): Add die sound
  state = State::Die;
  animator->TransitToAnimationState(static_cast<int>(state), 0.2f);
  stateElapsed = 0.f;
  collider->SetActive(false);
}

// client callback
void Enemy::ChangeState(int newState) {
  state = static_cast<State>(newState);
  animator->TransitToAnimationState(newState, 0.2f);
  stateElapsed = 0.f;
}

void Enemy::OnReachTarget(Transform* target) {
  transform->LookAt(target->GetWorldPos());

  NetworkManager::Instance()
      .SendMessageFromServerToAll<EnemyStateChangeMessage>(
          [this](EnemyStateChangeMessage* message) {
            message->enemyIndex = enemyIndex;
            message->newState = static_cast<int>(State::Punch);
          });

  auto name = target->entity->GetName();
  PlayerController* player = target->entity->GetComponent<PlayerController>();
  ASSERT(player != nullptr);
  NetworkManager::Instance().SendMessageFromServerToAll<PlayerDamageMessage>(
      [player, this](PlayerDamageMessage* message) {
        message->playerIndex = player->playerIndex;
        message->damage = attackDamage;
      });
}
