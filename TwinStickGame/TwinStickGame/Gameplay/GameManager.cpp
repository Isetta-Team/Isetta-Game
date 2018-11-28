/*
 * Copyright (c) 2018 Isetta
 */
#include "Gameplay/GameManager.h"
#include <Networking/NetworkManager>
#include <Core/IsettaCore.h>

using namespace Isetta;

GameManager& GameManager::Instance() {
  return *instance;
}

void GameManager::Awake() {
  instance = this;
}

void GameManager::Update() {
}

void GameManager::LoadLevel(std::string_view levelName) {
	if (NetworkManager::Instance().IsHost()) {
		auto loadLevelMsg = NetworkManager::Instance().GenerateMessageFromServer<LoadLevelMessage>(0);
		strcpy_s(loadLevelMsg->levelName, levelName.data());
		NetworkManager::Instance().SendMessageFromServerToAll<LoadLevelMessage>(loadLevelMsg);
	}
}

void GameManager::RegisterLoadLevelCallback() {
	U64 handle1 = NetworkManager::Instance().RegisterClientCallback<LoadLevelMessage>(
              [](yojimbo::Message* message) {
                auto* loadLevelMsg = reinterpret_cast<LoadLevelMessage>(message);
                LevelManager::Instance().LoadLevel(loadLevelMsg->levelName);
              });
        U64 handle2 = NetworkManager::Instance().AddDisconnectedFromServerListener([handle1, handle2](){
          NetworkManager::Instance().UnregisterClientCallback(handle);
          NetworkManager::Instance().RemoveDIsconnectedFromServerListener(handle2);
        });
}