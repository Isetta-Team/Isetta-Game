/*
 * Copyright (c) 2018 Isetta
 */
#pragma once
#include "Scene/Component.h"

using namespace Isetta;

DEFINE_COMPONENT(Score, Component, true)
private:
int score = 0;

public:
void GuiUpdate() override;
DEFINE_COMPONENT_END(Score, Component)