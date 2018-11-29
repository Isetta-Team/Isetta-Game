/*
 * Copyright (c) 2018 Isetta
 */
#include "Gameplay/GameManager.h"

#include <Core/IsettaCore.h>
#include <Networking/NetworkManager.h>
// #include "Networking/NetworkMessages.h"

using namespace Isetta;

GameManager& GameManager::Instance() {
  static GameManager instance;
  return instance;
}

void GameManager::LoadLevel(std::string_view levelName) const {
  if (NetworkManager::Instance().IsHost()) {
    // auto loadLevelMsg =
        // NetworkManager::Instance().GenerateMessageFromServer<LoadLevelMessage>(
            // 0);
    // strcpy_s(loadLevelMsg->levelName, levelName.data());
    // NetworkManager::Instance().SendMessageFromServerToAll<LoadLevelMessage>(
        // loadLevelMsg);
  }
}

void GameManager::RegisterLoadLevelCallback() const {
  // int handle1 =
      // NetworkManager::Instance().RegisterClientCallback<LoadLevelMessage>(
          // [](yojimbo::Message* message) {
            // auto* loadLevelMsg = reinterpret_cast<LoadLevelMessage*>(message);
            // LevelManager::Instance().LoadLevel(loadLevelMsg->levelName);
          // });
  // int handle2 = NetworkManager::Instance().AddDisconnectedFromServerListener(
      // [handle1, handle2]() {
        // NetworkManager::Instance().UnregisterClientCallback<LoadLevelMessage>(
            // handle1);
        // NetworkManager::Instance().RemoveDisconnectedFromServerListener(
            // handle2);
      // });
}
