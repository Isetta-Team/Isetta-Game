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
#include "Menu/MainMenu.h"
#include "Menu/MainMenuDraw.h"
#include <Audio/AudioClip.h>

using namespace Isetta;

void MenuLevel::OnLevelLoad() {
  Font::AddFontFromFile("fonts\\NeonAbsoluteSans.ttf", 16.f, "Neon");
  Font::AddFontFromFile("fonts\\NeonAbsoluteSans.ttf", 50.f, "Neon");
  Font::AddFontFromFile("fonts\\NeonAbsoluteSans.ttf", 100.f, "Neon");

  Entity* cameraEntity = Entity::CreateEntity("Camera");
  cameraEntity->AddComponent<CameraComponent>();
  cameraEntity->SetTransform(Math::Vector3{0, 5, 10}, Math::Vector3{-15, 0, 0},
                             Math::Vector3::one);
  cameraEntity->AddComponent<AudioListener>();

  Entity* mainMenu = Entity::CreateEntity("MainMenu");
  mainMenu->AddComponent<MainMenu>();
  mainMenu->AddComponent<MainMenuDraw>();
  mainMenu->AddComponent<AudioSource>(0b000, AudioClip::LoadClip("audio/button.wav"));

  Entity* manager = Entity::CreateEntity("Manager");
  auto bgm = manager->AddComponent<AudioSource>(
      0b010, AudioClip::LoadClip("audio/bgm/Signal-in-the-Noise.mp3"));
  // bgm->SetVolume(0.1f);
  // bgm->Play();
}
