/*
 * Copyright (c) 2018 Isetta
 */
#pragma once
#include <IsettaEngine.h>

using namespace Isetta;

DEFINE_COMPONENT(CameraController, Component, true)
public:
void Update() override;
void GuiUpdate() override;
private:
Math::Vector3 offset{0, 15, 10};
DEFINE_COMPONENT_END(CameraController, Component)
