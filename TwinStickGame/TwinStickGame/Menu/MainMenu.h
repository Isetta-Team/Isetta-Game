/*
 * Copyright (c) 2018 Isetta
 */
#pragma once
#include <SID/sid.h>
#include <stack>
#include "Core/Math/Vector3.h"
#include "Graphics/Texture.h"
#include "Networking/NetworkDiscovery.h"
#include "Scene/Component.h"
using namespace Isetta;

namespace Isetta {
class AudioSource;
}

BEGIN_COMPONENT(MainMenu, Isetta::Component, true)
private:
void Start() override;
void Update() override;
void GuiUpdate() override;
void OnMessageReceived(const char* data, const char* ip);

float btnLerpFactor = 0.0f;
float btnSpeed = 2.f;

char ipAddress[16]{};
int playerCnt = 0;

Texture backgroundTexture;
AudioSource* buttonAudio{nullptr};

enum class MenuState : U16 { MainMenu = 0, Multiplayer, Host, Client, InRoom};
MenuState menuState{MenuState::MainMenu};
std::stack<Action<>> onCancel;
NetworkDiscovery* networkDiscovery{nullptr};

struct HostInfo {
  std::string ip;
  std::string name;
  float remainTime;
};

std::unordered_map<StringId, HostInfo> availableHosts;
float broadcastInterval = 0.2f;

END_COMPONENT(MainMenu, Isetta::Component)
