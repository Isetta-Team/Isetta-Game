/*
 * Copyright (c) 2018 Isetta
 */
#include <IsettaEngine.h>
#include "Gameplay/EntityFactory.h"

#include <Components/Editor/EditorComponent.h>
#include <Components/NetworkMonitor.h>

#include "Player/PlayerController.h"
#include "Test/NetworkTestComp.h"

using namespace Isetta;

Entity* EntityFactory::CreateNetworkEntity() {
  Entity* entity = Entity::Instantiate("Network Entity");
  entity->AddComponent<NetworkTestComp>();
  entity->AddComponent<NetworkMonitor>();
  return entity;
}

Entity* EntityFactory::CreateDebugEntity() {
  Entity* entity = Entity::Instantiate("Debug");
  entity->AddComponent<EditorComponent>();
  return entity;
}

Entity* EntityFactory::CreatePlayer(const std::string_view playerName) {
  Entity* player = Entity::Instantiate(playerName.data());
  player->AddComponent<PlayerController>();
  player->transform->SetLocalScale(Math::Vector3::one * 0.01f);
  return player;
}
