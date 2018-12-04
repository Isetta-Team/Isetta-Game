/*
 * Copyright (c) 2018 Isetta
 */
#pragma once
#include <IsettaEngine.h>

using namespace Isetta;

DEFINE_COMPONENT(MainMenuDraw, Isetta::Component, true)
private:
Math::Vector3 gridPosition = Math::Vector3::zero;
float gridSpeed = 1.f;

void Update() override;
DEFINE_COMPONENT_END(MainMenuDraw, Isetta::Component)