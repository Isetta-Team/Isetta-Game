/*
 * Copyright (c) 2018 Isetta
 */
#include "Gameplay/GameManager.h"
#include <Core/IsettaCore.h>

using namespace Isetta;

GameManager& GameManager::Instance() {
  return *instance;
}

void GameManager::Awake() {
  instance = this;
}

void GameManager::Update() {
  LOG_INFO(Debug::Channel::Gameplay, "Name: %s", gameConfig.playerName.GetVal().c_str());
}
