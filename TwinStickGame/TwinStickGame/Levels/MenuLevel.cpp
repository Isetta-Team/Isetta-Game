/*
 * Copyright (c) 2018 Isetta
 */
#include "MenuLevel.h"

// ENGINE
#include "Audio/AudioListener.h"
#include "Audio/AudioSource.h"
#include "Graphics/CameraComponent.h"
#include "Graphics/Font.h"
#include "Scene/Entity.h"

// GAME
#include <Audio/AudioClip.h>
#include "Menu/MainMenu.h"
#include "Menu/MainMenuDraw.h"
#include "Consts.h"
#include "Gameplay/GameManager.h"

using namespace Isetta;

void MenuLevel::OnLevelLoad() {
  Font::AddFontFromFile("fonts\\NeonAbsoluteSans.ttf", Consts::SMALL_SIZE, "Neon");
  Font::AddFontFromFile("fonts\\NeonAbsoluteSans.ttf", Consts::MID_SIZE, "Neon");
  Font::AddFontFromFile("fonts\\NeonAbsoluteSans.ttf", Consts::TITLE_SIZE, "Neon");

  Entity* cameraEntity = Entity::Instantiate("Camera");
  cameraEntity->AddComponent<CameraComponent>();
  cameraEntity->SetTransform(Math::Vector3{0, 5, 10}, Math::Vector3{-15, 0, 0},
                             Math::Vector3::one);
  cameraEntity->AddComponent<AudioListener>();

  Entity* mainMenu = Entity::Instantiate("MainMenu");
  mainMenu->AddComponent<MainMenu>();
  mainMenu->AddComponent<MainMenuDraw>();
  mainMenu->AddComponent<AudioSource>(
      0b000, AudioClip::Load("audio/button.wav", "button-click"));

  Entity* manager = Entity::Instantiate("Game Manager");
  auto bgm = manager->AddComponent<AudioSource>(
      0b010, AudioClip::Load("audio/bgm/Signal-in-the-Noise.mp3", "bgm"));
  bgm->SetVolume(0.4f);
  bgm->Play();
  manager->AddComponent<GameManager>();
}
