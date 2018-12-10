/*
 * Copyright (c) 2018 Isetta
 */
#include "MenuLevel.h"
#include <IsettaEngine.h>

#include <Components/Editor/EditorComponent.h>
#include <Components/FlyController.h>
#include <Components/GridComponent.h>
#include <Components/JointFollow.h>
#include "Consts.h"
#include "Gameplay/EntityFactory.h"
#include "Gameplay/GameManager.h"
#include "Menu/MainMenu.h"
#include "Menu/OrbitFollow.h"

using namespace Isetta;

void MenuLevel::Load() {
  GameManager::Instance();

  Font::AddFontFromFile("fonts\\DeatheMaach.otf", Consts::SMALL_SIZE, "Deathe");
  Font::AddFontFromFile("fonts\\DeatheMaach.otf", Consts::MID_SIZE, "Deathe");
  Font::AddFontFromFile("fonts\\DeatheMaach.otf", Consts::TITLE_SIZE, "Deathe");

  Entity* cameraEntity = Entity::Instantiate("Camera");
  cameraEntity->AddComponent<CameraComponent>();
  cameraEntity->SetTransform(Math::Vector3{-25, 10, 25}, Math::Vector3{0, 0, 0},
                             Math::Vector3::one);
  cameraEntity->AddComponent<AudioListener>();
  cameraEntity->AddComponent<OrbitFollow>(20, Math::Vector3{-30, 0, 25});

  Entity* lightEntity = Entity::Instantiate("Light");
  auto light = lightEntity->AddComponent<LightComponent>();
  lightEntity->SetTransform(Math::Vector3{-30, 10, 30}, Math::Vector3{0, 0, 0},
                            Math::Vector3::one);
  light->SetProperty<LightComponent::Property::FOV>(360);
  light->SetProperty<LightComponent::Property::RADIUS>(30);
  light->SetProperty<LightComponent::Property::COLOR_MULTIPLIER>(0.3f);

  Entity* mainMenu = Entity::Instantiate("MainMenu");
  mainMenu->AddComponent<MainMenu>();
  mainMenu->AddComponent<AudioSource>(
      0b000, AudioClip::Load("audio/button.wav", "button-click"));

  Entity* manager = Entity::Instantiate("Sound Manager");
  auto bgm = manager->AddComponent<AudioSource>(
      0b010, AudioClip::Load("audio/bgm/bullethell-v1.mp3", "bgm"));
  bgm->SetVolume(0.4f);
  bgm->Play();

  level.Load();

  Entity* player = Entity::Instantiate("Player");
  player->transform->SetWorldPos(Math::Vector3{-30, 0, 25});
  player->transform->SetLocalScale(0.01f * Math::Vector3::one);
  auto playerMesh =
      player->AddComponent<MeshComponent>("models\\Player\\Vanguard.scene.xml");
  auto playerAnim = player->AddComponent<AnimationComponent>(playerMesh);
  playerAnim->AddAnimation("models\\Player\\Player_Idle.anim");

  Entity* weapon = Entity::Instantiate("Weapon");
  weapon->transform->SetLocalScale(Math::Vector3{0.75f});
  weapon->AddComponent<MeshComponent>(
      "models\\Weapons\\flamethrower.scene.xml");
  weapon->AddComponent<JointFollow>(playerMesh, "mixamorig_RightHand",
                                    Math::Vector3{0.1f, 0, 0.4f},
                                    Math::Vector3{0, 180, 100});

  Entity* enemy = Entity::Instantiate("Enemy");
  enemy->transform->SetWorldPos(Math::Vector3{-38, 0, 12});
  auto enemyMesh =
      enemy->AddComponent<MeshComponent>("models\\Enemy\\idle.scene.xml");
  auto enemyAnim = enemy->AddComponent<AnimationComponent>(enemyMesh);
  enemyAnim->AddAnimation("models\\Enemy\\idle.anim");

  enemy = Entity::Instantiate("Enemy");
  enemy->transform->SetWorldPos(Math::Vector3{-15, 0, 30});
  enemy->transform->SetLocalRot(Math::Vector3{0, -90, 0});
  enemyMesh =
      enemy->AddComponent<MeshComponent>("models\\Enemy\\idle.scene.xml");
  enemyAnim = enemy->AddComponent<AnimationComponent>(enemyMesh);
  enemyAnim->AddAnimation("models\\Enemy\\idle.anim");

  enemy = Entity::Instantiate("Enemy");
  enemy->transform->SetWorldPos(Math::Vector3{-40, 0, 40});
  enemy->transform->SetLocalRot(Math::Vector3{0, 145, 0});
  enemyMesh =
      enemy->AddComponent<MeshComponent>("models\\Enemy\\idle.scene.xml");
  enemyAnim = enemy->AddComponent<AnimationComponent>(enemyMesh);
  enemyAnim->AddAnimation("models\\Enemy\\idle.anim");

  // EntityFactory::CreateNetworkEntity();
}
