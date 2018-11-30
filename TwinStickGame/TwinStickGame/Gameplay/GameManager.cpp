/*
 * Copyright (c) 2018 Isetta
 */
#include "Gameplay/GameManager.h"

#include <Core/IsettaCore.h>
#include <Networking/NetworkManager.h>
// #include "Networking/NetworkMessages.h"

using namespace Isetta;

GameManager::GameConfig GameManager::gameConfig;

GameManager& GameManager::Instance() {
  static GameManager instance;
  return instance;
}

void GameManager::LoadLevel(std::string_view levelName) const {
  if (NetworkManager::Instance().IsHost()) {
  }
}

void GameManager::RegisterLoadLevelCallback() const {
}
