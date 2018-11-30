/*
 * Copyright (c) 2018 Isetta
 */
#pragma once
#include <Scene/Component.h>

using namespace Isetta;

BEGIN_COMPONENT(PlayerController, Component, true)
public:
void Start() override;
void Update() override;

private:
float scale{0.01f};
float moveSpeed{15.0f};
bool isMoving{false};
float lookSmooth{30.f};

END_COMPONENT(PlayerController, Component)
