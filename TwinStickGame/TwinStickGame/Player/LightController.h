/*
 * Copyright (c) 2018 Isetta
 */
#pragma once
#include <IsettaEngine.h>

using namespace Isetta;

DEFINE_COMPONENT(LightController, Component, true)
public:
void Update() override;
LightController(Entity* player) : player(player) {}

private:
Math::Vector3 offset{0, 100, 0};
Entity* player{nullptr};
DEFINE_COMPONENT_END(LightController, Component)
