/*
 * Copyright (c) 2018 Isetta
 */
#include "Gameplay/EntityFactory.h"

#include <Components/Editor/EditorComponent.h>
#include <Components/GridComponent.h>
#include <Components/NetworkMonitor.h>
#include <Scene/Primitive.h>

#include "Player/PlayerController.h"
#include "Player/PlayerHealth.h"
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
  entity->AddComponent<GridComponent>();
  return entity;
}

Entity* EntityFactory::CreatePlayer(const std::string_view playerName) {
  // Entity* player = Primitive::Create(Primitive::Type::Capsule);
  Entity* player = Entity::Instantiate("");
  player->SetName(playerName);
  player->AddComponent<PlayerHealth>();
  player->AddComponent<PlayerController>();
  return player;
}
