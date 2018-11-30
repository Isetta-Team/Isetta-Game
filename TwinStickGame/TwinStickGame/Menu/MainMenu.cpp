/*
 * Copyright (c) 2018 Isetta
 */
#include "MainMenu.h"

// ENGINE
#include "Application.h"
#include "Audio/AudioClip.h"
#include "Audio/AudioSource.h"
#include "Core/Color.h"
#include "Core/SystemInfo.h"
#include "Core/Time/Time.h"
#include "Graphics/Font.h"
#include "Graphics/GUI.h"
#include "Graphics/RectTransform.h"
#include "Networking/NetworkDiscovery.h"
#include "Scene/Entity.h"
#include "Scene/LevelManager.h"
#include "Util.h"
#include "imgui/imgui.h"

// GAME
#include "ColorScheme.h"
#include "Consts.h"
#include "Gameplay/GameManager.h"
#include "Gameplay/Score.h"

using namespace Isetta;

void MainMenu::Start() {
  backgroundTexture = Texture{"images\\Neon-background.png"};
  buttonAudio = entity->GetComponent<AudioSource>();
  buttonAudio->SetVolume(0.25f);
  networkDiscovery = entity->AddComponent<NetworkDiscovery>();
}

void MainMenu::Update() {
  for (auto& host : availableHosts) {
    HostInfo info = host.second;
    info.remainTime -= Time::GetDeltaTime();
    host.second = info;
  }
}

void MainMenu::GuiUpdate() {
  GUI::Image(
      RectTransform{
          {0, -325, 2.f * static_cast<float>(backgroundTexture.GetWidth()),
           1.75f * static_cast<float>(backgroundTexture.GetHeight())},
          GUI::Pivot::Top,
          GUI::Pivot::Top},
      backgroundTexture);

  RectTransform rect{{0, -100, 0, 0}, GUI::Pivot::Center, GUI::Pivot::Center};
  GUI::Text(rect, "GAME NAME",
            GUI::TextStyle{ColorScheme::NEON_BLUE, Consts::TITLE_SIZE, "Neon"});

  const float width = 500.f, height = 75.f, padding = 25.f;
  rect.rect.y = 0.f;
  rect.rect.width = width;
  rect.rect.height = height;

  const GUI::ButtonStyle btnStyle{ColorScheme::SUNSET_LIGHT,
                                  ColorScheme::SUNSET_MEDIUM,
                                  ColorScheme::SUNSET_DARK};

  const Color sunsetLightAlpha{ColorScheme::SUNSET_LIGHT.r,
                               ColorScheme::SUNSET_LIGHT.g,
                               ColorScheme::SUNSET_LIGHT.b, 0.25f};

  const GUI::InputStyle ipStyle{sunsetLightAlpha, sunsetLightAlpha,
                                sunsetLightAlpha, Color::white};
  const GUI::TextStyle textStyle{Color::white, Consts::MID_SIZE, "Neon"};

  struct FilterIP {
    static int Filter(InputTextCallbackData* data) {
      if (isdigit(data->EventChar) || data->EventChar == '.') return 0;
      return 1;
    }
  };

  Font::PushFont("Neon", Consts::MID_SIZE);
  if (menuState == MenuState::MainMenu) {
    if (GUI::Button(rect, "SINGLE PLAYER", btnStyle)) {
      buttonAudio->Play();
      LevelManager::Instance().LoadLevel("SinglePlayerLevel");
    }
    rect.rect.y += height + padding;

    if (GUI::Button(rect, "MULTIPLAYER", btnStyle)) {
      buttonAudio->Play();
      menuState = MenuState::Multiplayer;
      onCancel.push([this]() { this->menuState = MenuState::MainMenu; });
    }
    rect.rect.y += height + padding;

    if (GUI::Button(rect, "EXIT", btnStyle)) {
      buttonAudio->Play();
      Application::Exit();
    }

  } else {
    if (menuState == MenuState::Multiplayer) {
      if (GUI::Button(rect, "HOST", btnStyle)) {
        buttonAudio->Play();
        menuState = MenuState::Host;
        networkDiscovery->StartBroadcasting(
            GameManager::gameConfig.playerName.GetVal(), 600,
            broadcastInterval);

        NetworkManager::Instance().StartHost(SystemInfo::GetIpAddressWithPrefix(
            CONFIG_VAL(networkConfig.ipPrefix)));

        onCancel.push([this]() {
          this->menuState = MenuState::Multiplayer;
          this->networkDiscovery->StopBroadcasting();
          NetworkManager::Instance().StopHost();
        });
      }

      rect.rect.y += height + padding;
      if (GUI::Button(rect, "CONNECT", btnStyle)) {
        buttonAudio->Play();
        menuState = MenuState::Client;
        static U64 handle = networkDiscovery->AddOnMessageReceivedListener(
            [this](const char* data, const char* ip) {
              this->OnMessageReceived(data, ip);
            });
        networkDiscovery->StartListening();

        onCancel.push([=]() {
          this->menuState = MenuState::Multiplayer;
          this->networkDiscovery->RemoveOnMessageReceivedListener(handle);
          this->networkDiscovery->StopListening();
        });
      }

    } else if (menuState == MenuState::Host) {
      rect.rect.y += height + padding;

      GUI::Child(rect, "host_options", [&]() {
        RectTransform localRect{
            {0, 0, 0, 0}, GUI::Pivot::Left, GUI::Pivot::Left};
        GUI::Text(localRect, "Players: ", textStyle);

        localRect.anchor = GUI::Pivot::Right;
        localRect.pivot = GUI::Pivot::Right;
        const char* players = Util::StrFormat("%d/4", playerCnt);
        GUI::Text(localRect, players, textStyle);
      });

      RectTransform rectCpy{rect};
      btnLerpFactor += btnSpeed * Time::GetDeltaTime();
      btnLerpFactor = Math::Util::Min(btnLerpFactor, 1);
      rectCpy.rect.y =
          rect.rect.y - Math::Util::Lerp(0, height + padding, btnLerpFactor);
      GUI::Child(rectCpy, "host_ready", [&]() {
        RectTransform localRect{{0, 0, rect.rect.width, rect.rect.height}};
        if (GUI::Button(localRect, "START!", btnStyle)) {buttonAudio->Play();
        GameManager::Instance().LoadLevel("Level1");
        }
      });
    } else if (menuState == MenuState::Client) {
      int actualHosts = 0;
      RectTransform rectCpy{rect};
      rectCpy.rect.y += height + 10.f;
      rectCpy.rect.width -= padding;
      rectCpy.rect.height = 2 * height - 10.f;
      GUI::Child(rectCpy, "lobbies", [&]() {
        for (auto& host : availableHosts) {
          if (host.second.remainTime <= 0.f) continue;
          const char* ip = host.second.ip.c_str();
          std::string name = host.second.name;
          name += "\'s Game";

          const float btnHeight = 60.f;
          RectTransform localRect{
              Math::Rect{0, actualHosts * (btnHeight + 10) + 10, 0, 0},
              GUI::Pivot::TopLeft, GUI::Pivot::TopLeft};
          GUI::Text(localRect, name, textStyle);

          localRect.anchor = GUI::Pivot::TopRight;
          localRect.pivot = GUI::Pivot::TopRight;
          localRect.rect.y -= 5;
          localRect.rect.width = 130;
          localRect.rect.height = btnHeight;
          if (GUI::Button(localRect, "JOIN!", btnStyle)) {
            buttonAudio->Play();
            NetworkManager::Instance().StartClient(ip);
            menuState = MenuState::InRoom;
            onCancel.push([this]() {
              this->menuState = MenuState::Client;
              NetworkManager::Instance().StopClient();
            });
          }
          ++actualHosts;
        }
      });
      if (actualHosts > 0) {
        dotElapsed += 2.5f * Time::GetDeltaTime();
        if (dotElapsed > 4.f) dotElapsed = 0;
        const int dotCnt = Math::Util::FloorToInt(dotElapsed);
        std::string dots;
        for (int i = 0; i < dotCnt; i++) dots += ".";
        GUI::Text(rect, "LOOKING FOR HOSTS" + dots, textStyle);
      }
      rect.rect.y += height + padding;
    } else if (menuState == MenuState::InRoom) {
      GUI::Text(rect, "WAITING FOR START", textStyle);
      rect.rect.y += height + padding;
    }

    rect.rect.y += height + padding;
    if (GUI::Button(rect, "CANCEL", btnStyle)) {
      buttonAudio->Play();
      if (!onCancel.empty()) {
        onCancel.top()();
        onCancel.pop();
      }
      btnLerpFactor = 0;
    }
  }
  Font::PopFont();
}

void MainMenu::OnMessageReceived(const char* data, const char* ip) {
  auto host = availableHosts.find(SID(ip));
  if (host != availableHosts.end()) {
    HostInfo info = host->second;
    info.remainTime = broadcastInterval + 0.1f;
    host->second = info;
  } else {
    HostInfo info;
    info.ip = ip;
    info.name = data;
    info.remainTime = broadcastInterval + 0.1f;
    availableHosts.insert({SID(ip), info});
  }
}
