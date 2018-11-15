/*
 * Copyright (c) 2018 Isetta
 */
#pragma once
#include "Scene/Component.h"

using namespace Isetta;

BEGIN_COMPONENT(PlayerHealth, Component, true)
private:
class Damageable* health;

public:
void Start() override;
void GuiUpdate() override;
END_COMPONENT(PlayerHealth, Component)
