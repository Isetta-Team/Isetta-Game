/*
 * Copyright (c) 2018 Isetta
 */
#include "MenuLevel.h"

// ENGINE
#include "Core/Config/Config.h"
#include "Graphics/CameraComponent.h"
#include "Graphics/GUI.h"
#include "Scene/Entity.h"

// GAME
#include "Menu/MainMenu.h"
#include "Menu/MainMenuDraw.h"

using namespace Isetta;
using CameraProperty = CameraComponent::Property;

void MenuLevel::LoadLevel() {
  GUI::AddFontFromFile("Resources\\fonts\\NeonAbsoluteSans.ttf", 16.f, "Neon");
  GUI::AddFontFromFile("Resources\\fonts\\NeonAbsoluteSans.ttf", 50.f, "Neon");
  GUI::AddFontFromFile("Resources\\fonts\\NeonAbsoluteSans.ttf", 100.f, "Neon");

  Entity* cameraEntity{AddEntity("Camera")};
  CameraComponent* camComp =
      cameraEntity->AddComponent<CameraComponent, true>("Camera");
  cameraEntity->SetTransform(Math::Vector3{0, 5, 10}, Math::Vector3{-15, 0, 0},
                             Math::Vector3::one);
  camComp->SetProperty<CameraProperty::FOV>(
      CONFIG_VAL(renderConfig.fieldOfView));
  camComp->SetProperty<CameraProperty::NEAR_PLANE>(
      CONFIG_VAL(renderConfig.nearClippingPlane));
  camComp->SetProperty<CameraProperty::FAR_PLANE>(70);

  Entity* mainMenu{AddEntity("MainMenu")};
  mainMenu->AddComponent<MainMenu>();
  mainMenu->AddComponent<MainMenuDraw>();
}
