/*
 * Copyright (c) 2018 Isetta
 */
#include <IsettaEngine.h>

#include "Enemy/Enemy.h"
#include "Gameplay/Damageable.h"
#include "Networking/NetworkMessages.h"

using namespace Isetta;

void Enemy::Awake() {
  auto* collider = entity->AddComponent<CapsuleCollider>();
  collider->center = Math::Vector3::up * 1.f;

  damageable = entity->AddComponent<Damageable>(100);
  damageable->deathDelegate.Subscribe([this](int playerIndex) {
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

  // animator->TransitToAnimationState(0, 0.2f);
  dieAnimationDuration = 1.8f;
  animator->Stop();
}

void Enemy::Update() {
  // TODO(YIDI): Only do path finding on server
  switch (state) {
    case State::Die:
      dieElapsed += Time::GetDeltaTime();
      if (dieElapsed > dieAnimationDuration) {
        entity->SetActive(false);
      }
      break;
    default:
      break;
  }
}

void Enemy::Reanimate() {
  // TODO(YIDI):  Follow player
  state = State::Run;
  animator->TransitToAnimationState(static_cast<int>(state), 0.2f);
  damageable->Reset();
}

void Enemy::Die() {
  state = State::Die;
  animator->TransitToAnimationState(static_cast<int>(state), 0.2f);
  dieElapsed = 0.f;
}
