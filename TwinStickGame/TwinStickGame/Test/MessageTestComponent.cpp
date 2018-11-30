/*
 * Copyright (c) 2018 Isetta
 */

#include "MessageTestComponent.h"

#include "Core/IsettaCore.h"

void MessageTestComponent::GuiUpdate() {
  static bool isOpen = true;
  GUI::Window(
      RectTransform{Math::Rect{180, 80, 150, 50}, GUI::Pivot::Top,
                    GUI::Pivot::Top},
      "Network Monitor",
      [=]() {
        GUI::Text(RectTransform{Math::Rect{5, 0, 150, 50}},
                  Util::StrFormat("Counter: %d", counter));
      },
      &isOpen);
}