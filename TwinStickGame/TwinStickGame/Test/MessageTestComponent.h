/*
 * Copyright (c) 2018 Isetta
 */
#pragma once

#include "Scene/Component.h"

using namespace Isetta;

DEFINE_COMPONENT(MessageTestComponent, Component, false)
public:
void GuiUpdate() override;

int counter = 0;
DEFINE_COMPONENT_END(MessageTestComponent, Component)