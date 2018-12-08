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
  collider = entity->AddComponent<CapsuleCollider>();
  collider->center = Math::Vector3::up * 1.f;

  damageable = entity->AddComponent<Damageable>(100);
  // health is synced by HitEnemyMessage
  damageable->onDeath.Subscribe([this](int playerIndex) {
    if (NetworkManager::Instance().IsHost()) {
      NetworkManager::Instance().SendMessageFromServerToAll<ScoreMessage>(
          [this](ScoreMessage* message) { message->score = score; });
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
        if ((targetPos - transform->GetWorldPos()).Magnitude() > 0.05f) {
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
  animator->TransitToAnimationState(static_cast<int>(state), 0.2f);
  damageable->Reset();
  collider->SetActive(true);
}

void Enemy::Die() {
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
  // NetworkManager::Instance().SendMessageFromServerToAll<PlayerDamageMessage>(
  // [player, this](PlayerDamageMessage* message) {
  // message->playerIndex = player->playerIndex;
  // message->damage = attackDamage;
  // });
}
