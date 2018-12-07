/*
 * Copyright (c) 2018 Isetta
 */
#pragma once
#include <IsettaEngine.h>

using namespace Isetta;

DEFINE_COMPONENT(EnemyController, Component, true)
public:
void Awake() override;

private:
enum class State : U8 {
  Run = 0,
  Punch = 1,
  Die = 2
};

AnimationComponent* animator = nullptr;
State state = State::Run;

DEFINE_COMPONENT_END(EnemyController, Component)