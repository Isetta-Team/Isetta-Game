/*
 * Copyright (c) 2018 Isetta
 */
#pragma once

#include "Scene/Component.h"

using namespace Isetta;

BEGIN_COMPONENT(MessageTestComponent, Component, false)
public:
void GuiUpdate() override;

int counter = 0;
END_COMPONENT(MessageTestComponent, Component)