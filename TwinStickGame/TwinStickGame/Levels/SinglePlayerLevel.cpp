/*
 * Copyright (c) 2018 Isetta
 */
#include "SinglePlayerLevel.h"
#include <IsettaEngine.h>

// GAME
#include <Input/Input.h>
#include "Consts.h"
#include "Gameplay/Damageable.h"
#include "Player/PlayerHealth.h"

using namespace Isetta;
using CameraProperty = CameraComponent::Property;

void SinglePlayerLevel::Load() {
  // TODO: remove
  Font::AddFontFromFile("fonts\\DeatheMaach.otf", Consts::MID_SIZE, "Deathe");

  Entity* cameraEntity = Entity::Instantiate("Camera");
  cameraEntity->AddComponent<CameraComponent>();
  cameraEntity->SetTransform(Math::Vector3{0, 5, 10}, Math::Vector3{-15, 0, 0},
                             Math::Vector3::one);

  Entity* player = Entity::Instantiate("Player");
  auto damage = player->AddComponent<Damageable>(100);
  player->AddComponent<PlayerHealth>();

  Input::RegisterMousePressCallback(MouseButton::LEFT,
                                    [damage]() { damage->DealDamage(-1, 10); });

  Input::RegisterKeyPressCallback(KeyCode::ESCAPE,
                                  []() { Application::Exit(); });
}
