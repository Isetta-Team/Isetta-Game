/*
 * Copyright (c) 2018 Isetta
 */
#pragma once
#include <IsettaEngine.h>

using namespace Isetta;

namespace Isetta {
class NetworkId;
}

DEFINE_COMPONENT(PlayerController, Component, true)
public:
void Awake() override;
void Start() override;
void Update() override;

private:
static void RegisterNetworkCallbacks();
void Shoot();
Math::Vector3 GetBulletPos();

float moveSpeed{15.0f};
bool isMoving{false};

float shootInterval{0.1f};
float shootCooldown{0.f};

// Animation
enum class State : U8 {
  Idle, Run, Shoot, RunShoot, Die
};

AnimationComponent* animator = nullptr;
int idleState = 0;
int runState = 0;
int shootState = 0;
int runShootState = 0;
int dieState = 0;
State state = State::Idle;
float transitionDuration = 0.1f;

// Networking
NetworkId* networkId = nullptr;

DEFINE_COMPONENT_END(PlayerController, Component)
