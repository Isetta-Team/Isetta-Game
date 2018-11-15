/*
 * Copyright (c) 2018 Isetta
 */
#pragma once
#include "Scene/Component.h"

using namespace Isetta;

BEGIN_COMPONENT(Score, Component, true)
private:
int score = 0;

public:
void GuiUpdate() override;
END_COMPONENT(Score, Component)