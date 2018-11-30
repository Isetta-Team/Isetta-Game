/*
 * Copyright (c) 2018 Isetta
 */
#pragma once
#include "Scene/Component.h"

using namespace Isetta;

DEFINE_COMPONENT(PlayerHealth, Component, true)
private:
class Damageable* health;

public:
void Start() override;
void GuiUpdate() override;
DEFINE_COMPONENT_END(PlayerHealth, Component)
