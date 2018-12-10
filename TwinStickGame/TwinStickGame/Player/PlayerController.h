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
int GetScore() { return score; }

int playerIndex = 0;
bool isAlive{true};

private:
enum class State : int { Idle = 0, Run = 1, Shoot = 2, RunShoot = 3, Die = 4 };

static void RegisterNetworkCallbacks();
void CmdShoot();
void CmdChangeState(State newState) const;
Math::Vector3 GetBulletPos() const;

float moveSpeed{8.0f};
bool isMoving{false};

float shootInterval{0.2f};
float shootCooldown{0.f};
float shootSpeed{60.f};
Math::Vector3 bulletOffset{0, 100, 0};
float bulletRange{100.f};
float bulletDamage{20.f};
Entity* weapon = nullptr;

// Animation
AnimationComponent* animator = nullptr;
State state = State::Idle;
float transitionDuration = 0.1f;
float stateElapsed = 0.f;
float dieAnimationDuration = 54;
float isAnimationStopped = false;

AudioSource* audioComp = nullptr;
AudioClip* playerDamage = nullptr;
AudioClip* playerDie = nullptr;

// Networking
NetworkId* networkId = nullptr;

// Misc.
float score = 0;

DEFINE_COMPONENT_END(PlayerController, Component)
