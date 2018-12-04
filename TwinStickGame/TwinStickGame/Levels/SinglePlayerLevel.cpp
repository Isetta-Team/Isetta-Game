/*
 * Copyright (c) 2018 Isetta
 */
#include <IsettaEngine.h>
#include "SinglePlayerLevel.h"

// GAME
#include "Gameplay/Damageable.h"
#include "Gameplay/Score.h"
#include "Player/PlayerHealth.h"
#include <Input/Input.h>
#include "Consts.h"

using namespace Isetta;
using CameraProperty = CameraComponent::Property;

void SinglePlayerLevel::Load() {
  // TODO: remove
  Font::AddFontFromFile("fonts\\NeonAbsoluteSans.ttf", Consts::MID_SIZE, "Neon");

  Entity* cameraEntity = Entity::Instantiate("Camera");
  cameraEntity->AddComponent<CameraComponent>();
  cameraEntity->SetTransform(Math::Vector3{0, 5, 10}, Math::Vector3{-15, 0, 0},
                             Math::Vector3::one);

  Entity* score = Entity::Instantiate("Score");
  score->AddComponent<Score>();

  Entity* player = Entity::Instantiate("Player");
  player->AddComponent<Damageable>(100);
  player->AddComponent<PlayerHealth>();

  Input::RegisterKeyPressCallback(KeyCode::ESCAPE, []() {
    Application::Exit();
  });
}
