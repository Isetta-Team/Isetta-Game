/*
 * Copyright (c) 2018 Isetta
 */
#pragma once
#include <IsettaEngine.h>

using namespace Isetta;

DEFINE_COMPONENT(Enemy, Component, true)
public:
void Awake() override;
void Update() override;
void Reanimate();
void ChangeState(int newState);
int enemyIndex{0};

// server only
Nav2DAgent* agent{nullptr};
void OnReachTarget(Transform* target);

private:
enum class State : U8 { Run = 0, Punch = 1, Die = 2 };
const int score{1};
AnimationComponent* animator{nullptr};
State state{State::Run};
float speed = 3.f;
float attackDamage = 20.f;

// punch
float punchAnimationDuration{1.75f};

// die
void Die();
float stateElapsed{0.f};
float dieAnimationDuration{1.75f};

AudioSource* audioComp = nullptr;
AudioClip* enemyDamage = nullptr;

// particle
ParticleSystemComponent* particles = nullptr;

BoxCollider* collider;
class Damageable* damageable{nullptr};

DEFINE_COMPONENT_END(Enemy, Component)