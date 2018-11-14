/*
 * Copyright (c) 2018 Isetta
 */
#pragma once
#include "Core/Math/Vector3.h"
#include "Scene/Component.h"

using namespace Isetta;

BEGIN_COMPONENT(MainMenu, Isetta::Component, true)
private:
float readyLerpT = 0.0f;
float readyLerpSpeed = 2.f;

bool multiplayer = false;
char ipAddress[16] = "xxx.xxx.xxx.xxx";

void GuiUpdate() override;
END_COMPONENT(MainMenu, Isetta::Component)