/*
 * Copyright (c) 2018 Isetta
 */
#pragma once
#include <IsettaEngine.h>
using namespace Isetta;

namespace Isetta {
class AudioSource;
class NetworkDiscovery;
}  // namespace Isetta

DEFINE_COMPONENT(MainMenu, Isetta::Component, true)
private:
void Start() override;
void Update() override;
void GuiUpdate() override;
void OnMessageReceived(const char* data, const char* ip);

float btnLerpFactor = 0.0f;
float btnSpeed = 2.f;

float dotElapsed = 0;

Texture backgroundTexture;
AudioSource* buttonAudio{nullptr};

enum class MenuState : U16 { MainMenu = 0, Multiplayer, Host, Client, InRoom };
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

DEFINE_COMPONENT_END(MainMenu, Isetta::Component)
