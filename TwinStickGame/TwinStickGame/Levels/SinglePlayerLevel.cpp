/*
 * Copyright (c) 2018 Isetta
 */
#include "SinglePlayerLevel.h"

// ENGINE
#include "Core/Config/Config.h"
#include "Graphics/CameraComponent.h"
#include "Graphics/Font.h"
#include "Scene/Entity.h"

// GAME
#include "Gameplay/Damageable.h"
#include "Gameplay/Score.h"
#include "Player/PlayerHealth.h"
#include <Input/Input.h>
#include "Consts.h"

using namespace Isetta;
using CameraProperty = CameraComponent::Property;

void SinglePlayerLevel::OnLevelLoad() {
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
