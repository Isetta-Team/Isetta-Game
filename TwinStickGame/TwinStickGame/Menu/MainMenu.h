/*
 * Copyright (c) 2018 Isetta
 */
#pragma once
#include "Core/Math/Vector3.h"
#include "Graphics/Texture.h"
#include "Scene/Component.h"
#include <stack>
#include "Networking/NetworkDiscovery.h"

using namespace Isetta;

namespace Isetta {
class AudioSource;
}

BEGIN_COMPONENT(MainMenu, Isetta::Component, true)
private:
void Start() override;
void GuiUpdate() override;
float btnLerpFactor = 0.0f;
float btnSpeed = 2.f;

char ipAddress[16]{};
int playerCnt = 0;

Texture backgroundTexture;
AudioSource* buttonAudio{nullptr};

enum class MenuState : U16 { MainMenu = 0, Multiplayer, Host, Client };
MenuState menuState{MenuState::MainMenu};
std::stack<Action<>> onCancel;
NetworkDiscovery* networkDiscovery{nullptr};

END_COMPONENT(MainMenu, Isetta::Component)
