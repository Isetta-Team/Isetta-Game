/*
 * Copyright (c) 2018 Isetta
 */
#include <IsettaEngine.h>

#include "Enemy/EnemyController.h"

using namespace Isetta;

void EnemyController::Awake() {
  auto* mesh =
      entity->AddComponent<MeshComponent>("models/Enemy/running.scene.xml");
  animator = entity->AddComponent<AnimationComponent>(mesh);
  animator->AddAnimation("models/Enemy/running.anim");
  animator->AddAnimation("models/Enemy/punching.anim");
  animator->AddAnimation("models/Enemy/death.anim");
  entity->AddComponent<CapsuleCollider>();

  // Animation hack
  animator->TransitToAnimationState(static_cast<int>(State::Punch), 0.2f);
  animator->TransitToAnimationState(static_cast<int>(State::Run), 0.2f);
}
