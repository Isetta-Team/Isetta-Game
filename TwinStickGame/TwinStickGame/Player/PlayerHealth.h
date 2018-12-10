/*
 * Copyright (c) 2018 Isetta
 */
#pragma once
#include <IsettaEngine.h>

using namespace Isetta;

DEFINE_COMPONENT(PlayerHealth, Component, true)
private:
class Damageable* health = nullptr;
const float scale = 3.f;
float displayedHealth = 0;
float lerpHealth = 0;

public:
void Start() override;
void GuiUpdate() override;
DEFINE_COMPONENT_END(PlayerHealth, Component)
