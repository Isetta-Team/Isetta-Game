/*
 * Copyright (c) 2018 Isetta
 */
#include <IsettaEngine.h>

#include "Enemy/Enemy.h"
#include "Gameplay/Damageable.h"

using namespace Isetta;

void Enemy::Awake() {
  entity->AddComponent<CapsuleCollider>();
  auto* damageable = entity->AddComponent<Damageable>(100);

  damageable->deathDelegate.Subscribe([this](int playerIndex) {
    entity->SetActive(false);
  });

  auto* mesh =
      entity->AddComponent<MeshComponent>("models/Enemy/running.scene.xml");
  animator = entity->AddComponent<AnimationComponent>(mesh);
  animator->AddAnimation("models/Enemy/running.anim");
  animator->AddAnimation("models/Enemy/punching.anim");
  animator->AddAnimation("models/Enemy/death.anim");

  // Animation hack
  animator->TransitToAnimationState(static_cast<int>(State::Punch), 0.2f);
  animator->TransitToAnimationState(static_cast<int>(State::Run), 0.2f);
}

void Enemy::Update() {
  // TODO(YIDI): Only do path finding on server
}

void Enemy::Reanimate() {
  // TODO(YIDI):  Follow player
}
