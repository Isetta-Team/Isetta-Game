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
int enemyIndex{0};

private:
enum class State : U8 { Run = 0, Punch = 1, Die = 2 };
const int score{3};
AnimationComponent* animator{nullptr};
State state{State::Run};

DEFINE_COMPONENT_END(Enemy, Component)