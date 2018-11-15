/*
 * Copyright (c) 2018 Isetta
 */
#pragma once
#include "Core/Math/Vector3.h"
#include "Graphics/Texture.h"
#include "Scene/Component.h"

using namespace Isetta;

BEGIN_COMPONENT(MainMenu, Isetta::Component, true)
private:
float btnLerp = 0.0f;
float btnSpeed = 2.f;

std::bitset<2> multiplayer = 0;
char ipAddress[16];
int playerCnt = 0;

Texture backgroundTexture;

void Start() override;
void GuiUpdate() override;
END_COMPONENT(MainMenu, Isetta::Component)
