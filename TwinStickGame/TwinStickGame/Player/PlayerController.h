/*
 * Copyright (c) 2018 Isetta
 */
#pragma once
#include <IsettaEngine.h>

using namespace Isetta;

DEFINE_COMPONENT(PlayerController, Component, true)
public:
void Awake() override;
void Start() override;
void Update() override;
void GuiUpdate() override;

void ChangeState(int newState);
void Score(float score);

int playerIndex = 0;
private:
enum class State : int { Idle = 0, Run = 1, Shoot = 2, RunShoot = 3, Die = 4 };

static void RegisterNetworkCallbacks();
void CmdShoot();
void CmdChangeState(State newState) const;
Math::Vector3 GetBulletPos() const;

float moveSpeed{15.0f};
bool isMoving{false};
bool receiveInput{true};
float shootInterval{0.1f};
float shootCooldown{0.f};
float shootSpeed{60.f};
Math::Vector3 bulletOffset{0, 100, 0};
float bulletRange{100.f};
float bulletDamage{20.f};

// Animation
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

// Misc.
float score = 0;

DEFINE_COMPONENT_END(PlayerController, Component)
