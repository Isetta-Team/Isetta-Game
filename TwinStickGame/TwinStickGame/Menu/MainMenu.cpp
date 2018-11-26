/*
 * Copyright (c) 2018 Isetta
 */
#include "MainMenu.h"

// ENGINE
#include "Application.h"
#include "Audio/AudioClip.h"
#include "Audio/AudioSource.h"
#include "Core/Color.h"
#include "Core/Time/Time.h"
#include "Graphics/Font.h"
#include "Graphics/GUI.h"
#include "Graphics/RectTransform.h"
#include "Scene/Entity.h"
#include "Scene/LevelManager.h"
#include "Util.h"
#include "imgui/imgui.h"

// GAME
#include "ColorScheme.h"
#include "Gameplay/Score.h"
#include "Consts.h"

using namespace Isetta;

void MainMenu::Start() {
  backgroundTexture = Texture{"images\\Neon-background.png"};
  buttonAudio = entity->GetComponent<AudioSource>();
  buttonAudio->SetVolume(0.25f);
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
      onCancel.push([this]() {
        this->menuState = MenuState::MainMenu;
      });
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
        onCancel.push([this]() {
          this->menuState = MenuState::Multiplayer;
        });
      }

      rect.rect.y += height + padding;
      if (GUI::Button(rect, "CONNECT", btnStyle)) {
        buttonAudio->Play();
        menuState = MenuState::Client;
        onCancel.push([=]() {
          this->menuState = MenuState::Multiplayer;
        });
      }

    } else if (menuState == MenuState::Host) {
      if (GUI::Button(rect, "READY", btnStyle)) buttonAudio->Play();

      rect.rect.y += height + padding;
      GUI::Child(rect, "host_options", [&]() {
        RectTransform rect{{0, 0, 0, 0}, GUI::Pivot::Left, GUI::Pivot::Left};
        GUI::Text(rect,
                  "PLAYERS: ", GUI::TextStyle{Color::white, Consts::MID_SIZE, "Neon"});

        rect.anchor = GUI::Pivot::Right;
        rect.pivot = GUI::Pivot::Right;
        const char* players = Util::StrFormat("%d/4", playerCnt);
        GUI::Text(rect, players, GUI::TextStyle{Color::white, Consts::MID_SIZE, "Neon"});
      });
    } else if (menuState == MenuState::Client) {
      rect.rect.y += height + padding;
      GUI::InputText(rect, "IP:", ipAddress, sizeof(ipAddress), ipStyle,
                     GUI::InputTextFlags::CallbackCharFilter |
                         GUI::InputTextFlags::AlwaysInsertMode,
                     FilterIP::Filter);

      RectTransform rectCpy{rect};
      btnLerp += btnSpeed * Time::GetDeltaTime();
      btnLerp = Math::Util::Min(btnLerp, 1);
      rectCpy.rect.y =
          rect.rect.y - Math::Util::Lerp(0, height + padding, btnLerp);
      if (GUI::Button(rectCpy, "READY", btnStyle)) buttonAudio->Play();
    }

    rect.rect.y += height + padding;
    if (GUI::Button(rect, "CANCEL", btnStyle)) {
      buttonAudio->Play();
      if (!onCancel.empty()) {
        onCancel.top()();
        onCancel.pop();
      }
      btnLerp = 0;
    }
  }
  Font::PopFont();
}
