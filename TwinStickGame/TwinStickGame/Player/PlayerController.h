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
void GuiUpdate() override;

void ChangeState(int newState);

private:
static void RegisterNetworkCallbacks();
void CmdShoot();
Math::Vector3 GetBulletPos();

float moveSpeed{15.0f};
bool isMoving{false};

float shootInterval{0.1f};
float shootCooldown{0.f};

// Animation
enum class State : int {
  Idle = 0, Run = 1, Shoot = 2, RunShoot = 3, Die = 4
};

AnimationComponent* animator = nullptr;
// int idleState = 0;
// int runState = 0;
// int shootState = 0;
// int runShootState = 0;
// int dieState = 0;
State state = State::Idle;
float transitionDuration = 0.1f;

// Networking
NetworkId* networkId = nullptr;

DEFINE_COMPONENT_END(PlayerController, Component)
