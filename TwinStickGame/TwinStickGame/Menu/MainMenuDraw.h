/*
 * Copyright (c) 2018 Isetta
 */
#pragma once
#include "Core/Math/Vector3.h"
#include "Scene/Component.h"

using namespace Isetta;

BEGIN_COMPONENT(MainMenuDraw, Isetta::Component, true)
private:
Math::Vector3 gridPosition = Math::Vector3::zero;
float gridSpeed = 1.f;

void Update() override;
END_COMPONENT(MainMenuDraw, Isetta::Component)