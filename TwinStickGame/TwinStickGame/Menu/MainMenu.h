/*
 * Copyright (c) 2018 Isetta
 */
#pragma once
#include "Core/Math/Vector3.h"
#include "Graphics/Texture.h"
#include "Scene/Component.h"

using namespace Isetta;

namespace Isetta {
class AudioSource;
}

BEGIN_COMPONENT(MainMenu, Isetta::Component, true)
private:
float btnLerp = 0.0f;
float btnSpeed = 2.f;

char ipAddress[16];
int playerCnt = 0;
enum class MenuState : U16 {
  MainMenu = 0, Multiplayer, Host, Client
};

MenuState menuState {MenuState::MainMenu};

Texture backgroundTexture;
AudioSource* buttonAudio;

void Start() override;
void GuiUpdate() override;
END_COMPONENT(MainMenu, Isetta::Component)
