/*
 * Copyright (c) 2018 Isetta
 */
#include "MainMenu.h"

// ENGINE
#include "Application.h"
#include "Core/Color.h"
#include "Core/Time/Time.h"
#include "Graphics/GUI.h"
#include "Graphics/RectTransform.h"
#include "Scene/LevelManager.h"
#include "Util.h"
#include "imgui/imgui.h"

// GAME
#include "ColorScheme.h"

using namespace Isetta;

void MainMenu::Start() {
  backgroundTexture = Texture{"images\\Neon-background.png"};
}

void MainMenu::GuiUpdate() {
  ;
  GUI::Image(
      RectTransform{
          {0, -325, 2.f * static_cast<float>(backgroundTexture.GetWidth()),
           1.75f * static_cast<float>(backgroundTexture.GetHeight())},
          GUI::Pivot::Top,
          GUI::Pivot::Top},
      backgroundTexture);

  RectTransform rect{{0, -100, 0, 0}, GUI::Pivot::Center, GUI::Pivot::Center};
  GUI::Text(rect, "GAME NAME",
            GUI::TextStyle{ColorScheme::NEON_BLUE, 100.f, "Neon"});

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

  GUI::PushFont("Neon", 50.f);
  if (multiplayer.count() == 0) {
    if (GUI::Button(rect, "SINGLE PLAYER", btnStyle))
      LevelManager::Instance().LoadLevel("SinglePlayerLevel");
    rect.rect.y += height + padding;
    multiplayer.set(0, GUI::Button(rect, "MULTIPLAYER", btnStyle));
    rect.rect.y += height + padding;
    if (GUI::Button(rect, "EXIT", btnStyle)) Application::Exit();
  } else {
    if (!multiplayer.test(1)) {
      if (GUI::Button(rect, "HOST", btnStyle)) multiplayer.flip();
      rect.rect.y += height + padding;
      if (GUI::Button(rect, "CONNECT", btnStyle)) multiplayer.set(1, 1);
    } else if (!multiplayer.test(0)) {
      GUI::Button(rect, "READY", btnStyle);
      rect.rect.y += height + padding;
      GUI::Child(rect, "host_optiosn", [&]() {
        RectTransform rect{{0, 0, 0, 0}, GUI::Pivot::Left, GUI::Pivot::Left};
        GUI::Text(rect,
                  "PLAYERS: ", GUI::TextStyle{Color::white, 50.f, "Neon"});
        rect.anchor = GUI::Pivot::Right;
        rect.pivot = GUI::Pivot::Right;
        const char* players = Util::StrFormat("%d/4", playerCnt);
        GUI::Text(rect, players, GUI::TextStyle{Color::white, 50.f, "Neon"});
      });
    } else if (multiplayer.test(1)) {
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
      GUI::Button(rectCpy, "READY", btnStyle);
    }
    rect.rect.y += height + padding;
    if (GUI::Button(rect, "Cancel", btnStyle)) {
      multiplayer.set(0, multiplayer[1]);
      multiplayer.set(1, 0);
      btnLerp = 0;
    }
  }
  GUI::PopFont();
}
