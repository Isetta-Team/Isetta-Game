/*
 * Copyright (c) 2018 Isetta
 */
#include "PlayerHealth.h"

#include <IsettaEngine.h>

// GAME
#include "Consts.h"
#include "Gameplay/Damageable.h"
#include "Networking/NetworkMessages.h"

using namespace Isetta;

int PlayerHealth::authority = 0;
void PlayerHealth::Start() {
  health = entity->GetComponent<Damageable>();
  if (!health) {
    SetActive(false);
  }
  displayedHealth = health->GetMaxHealth();
  networkId = entity->GetComponent<NetworkId>();
  if (networkId->HasClientAuthority()) authority = networkId->clientAuthorityId;
}

void PlayerHealth::GuiUpdate() {
  float y = 60;
  float scale = mainScale;
  std::string name = player->entity->GetName();
  if (!networkId->HasClientAuthority()) {
    scale = smallScale;
    y += Math::Util::Max(authority, networkId->clientAuthorityId) * 60;
  }

  RectTransform rect{{30, y, 0, 0}};
  rect.pivot = GUI::Pivot::Left;
  GUI::Text(rect, name, GUI::TextStyle{Consts::MID_SIZE, "Deathe"});
  rect.pivot = GUI::Pivot::Left;
  rect.rect.x += 170.f;
  if (player->isAlive) {
    rect.rect.y -= 5.f;
    rect.rect.width = scale * health->GetMaxHealth();
    rect.rect.height = scale * 3 + 30.f;
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
  } else {
    GUI::Text(rect, "Dead!", GUI::TextStyle{Consts::MID_SIZE, "Deathe"});
  }
}
