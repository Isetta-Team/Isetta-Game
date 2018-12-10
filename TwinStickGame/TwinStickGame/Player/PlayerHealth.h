/*
 * Copyright (c) 2018 Isetta
 */
#pragma once
#include <IsettaEngine.h>
#include "PlayerController.h"

using namespace Isetta;

DEFINE_COMPONENT(PlayerHealth, Component, true)
private:
class Damageable* health = nullptr;
const float mainScale = 3.f, smallScale = 1.5f;
float displayedHealth = 0;
float lerpHealth = 0;
NetworkId* networkId = nullptr;
PlayerController* const player = nullptr;
static int authority;

public:
PlayerHealth() = default;
PlayerHealth(PlayerController* const player) : player{player} {}

void Start() override;
void GuiUpdate() override;
DEFINE_COMPONENT_END(PlayerHealth, Component)
