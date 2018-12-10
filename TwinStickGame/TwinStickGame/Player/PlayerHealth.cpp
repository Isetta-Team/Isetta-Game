/*
 * Copyright (c) 2018 Isetta
 */
#include "PlayerHealth.h"

#include <IsettaEngine.h>

// GAME
#include "Consts.h"
#include "Gameplay/Damageable.h"

using namespace Isetta;

void PlayerHealth::Start() {
  health = entity->GetComponent<Damageable>();
  if (!health) {
    SetActive(false);
  }
  displayedHealth = health->GetMaxHealth();
}

void PlayerHealth::GuiUpdate() {
  RectTransform rect{{30, 45, 0, 0}};
  rect.pivot = GUI::Pivot::Left;
  GUI::Text(rect, "Health:", GUI::TextStyle{Consts::MID_SIZE, "Deathe"});
  rect.pivot = GUI::Pivot::Left;
  rect.rect.y -= 3.f;
  rect.rect.x += 170.f;
  rect.rect.width = scale * health->GetMaxHealth();
  rect.rect.height = 40.f;
  GUI::Draw::RectFilled(rect, Color{187.f / 255, 187.f / 255, 187.f / 255});
  if (Math::Util::Abs(displayedHealth - health->GetHealth()) >
      Math::Util::EPSILON) {
    lerpHealth += 0.25f * Time::GetDeltaTime();
    displayedHealth = Math::Util::Lerp(
        displayedHealth, static_cast<float>(health->GetHealth()), lerpHealth);
  } else {
    lerpHealth = 0;
  }
  rect.rect.width = scale * displayedHealth;
  GUI::Draw::RectFilled(rect, Color{109.f / 255, 205.f / 255, 116.f / 255});
}
