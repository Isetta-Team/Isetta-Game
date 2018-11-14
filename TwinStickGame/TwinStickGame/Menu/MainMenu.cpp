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
#include "imgui/imgui.h"

// GAME
#include "ColorScheme.h"

using namespace Isetta;

void MainMenu::GuiUpdate() {
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
      if ((data->EventFlag &
           (ImGuiInputTextFlags)GUI::InputTextFlags::CallbackCharFilter) ==
          (ImGuiInputTextFlags)GUI::InputTextFlags::CallbackCharFilter) {
        if (isdigit(data->EventChar)) return 0;
        return 1;
      } else {
        if (data->BufTextLen < 15) {
          if (data->CursorPos % 4 == 3) {
            data->InsertChars(data->CursorPos--, ".");
            data->Buf[data->CursorPos] = 'x';
          } else {
            data->InsertChars(data->CursorPos, "x");
            --data->CursorPos;
          }
          return 0;
        }
        if (data->CursorPos % 4 == 3) ++data->CursorPos;
      }
    }
  };

  GUI::PushFont("Neon", 50.f);
  if (!multiplayer) {
    GUI::Button(rect, "SINGLE PLAYER", btnStyle);
    rect.rect.y += height + padding;
    multiplayer = GUI::Button(rect, "MULTIPLAYER", btnStyle);
    rect.rect.y += height + padding;
    if (GUI::Button(rect, "EXIT", btnStyle)) Application::Exit();
  } else {
    rect.rect.y += height + padding;
    GUI::InputText(rect, "IP:", ipAddress, sizeof(ipAddress), ipStyle,
                   GUI::InputTextFlags::CallbackCharFilter |
                       GUI::InputTextFlags::AlwaysInsertMode |
                       GUI::InputTextFlags::CallbackAlways,
                   FilterIP::Filter);

    RectTransform rectCpy{rect};
    readyLerpT += readyLerpSpeed * Time::GetDeltaTime();
    readyLerpT = Math::Util::Min(readyLerpT, 1);
    rectCpy.rect.y =
        rect.rect.y - Math::Util::Lerp(0, height + padding, readyLerpT);
    GUI::Button(rectCpy, "READY", btnStyle);
    rect.rect.y += height + padding;
    if (GUI::Button(rect, "Cancel", btnStyle)) {
      multiplayer = false;
      readyLerpT = 0;
    }
  }
  GUI::PopFont();
}