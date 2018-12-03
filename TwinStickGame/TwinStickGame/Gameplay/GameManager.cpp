/*
 * Copyright (c) 2018 Isetta
 */
#include "Gameplay/GameManager.h"

#include <Core/IsettaCore.h>
#include <Networking/NetworkId.h>
#include <Networking/NetworkManager.h>
#include <Networking/NetworkTransform.h>
#include "EntityFactory.h"
#include "Networking/NetworkMessages.h"

using namespace Isetta;

GameManager::GameConfig GameManager::gameConfig;

GameManager& GameManager::Instance() {
  static GameManager instance;
  return instance;
}

GameManager::GameManager() {
  RegisterClientConnectionCallbacks();
  RegisterClientLevelLoadedCallback();
  RegisterAllPlayerReadyCallback();
  RegisterSpawnPlayerCallbacks();
}

// ReSharper disable once CppMemberFunctionMayBeConst
void GameManager::SendSpawnPlayerMessage() {
  NetworkManager::Instance().SendMessageFromClient<SpawnPlayerMessage>(
      [](SpawnPlayerMessage* message) {
        strcpy_s(message->playerName, gameConfig.playerName.GetVal().c_str());
      });

  LOG_INFO(Debug::Channel::Networking,
           "Spawn player (%s) message sent from client",
           gameConfig.playerName.GetVal().c_str());
}

void GameManager::RegisterSpawnPlayerCallbacks() {
  NetworkManager::Instance().RegisterServerCallback<SpawnPlayerMessage>(
      [this](const int clientIndex, yojimbo::Message* inMessage) {
        auto* spawnMessage = reinterpret_cast<SpawnPlayerMessage*>(inMessage);
        Entity* player = EntityFactory::CreatePlayer(spawnMessage->playerName);
        NetworkId* networkId = player->AddComponent<NetworkId>();
        networkId->clientAuthorityId = clientIndex;

        player->AddComponent<NetworkTransform>();

        spawnMessage->netId = networkId->id;
        spawnMessage->clientAuthorityId = networkId->clientAuthorityId;
        spawnMessage->startPos = GetPlayerStartPos();

        NetworkManager::Instance()
            .SendMessageFromServerToAll<SpawnPlayerMessage>(spawnMessage);
        LOG_INFO(Debug::Channel::Networking,
                 "Spawn player message sent from sever for player (%s)",
                 spawnMessage->playerName);
      });

  NetworkManager::Instance().RegisterClientCallback<SpawnPlayerMessage>(
      [](yojimbo::Message* inMessage) {
        if (NetworkManager::Instance().IsHost()) {
          return;
        }

        auto* spawnMessage = reinterpret_cast<SpawnPlayerMessage*>(inMessage);
        Entity* player = EntityFactory::CreatePlayer(spawnMessage->playerName);
        NetworkId* networkId =
            player->AddComponent<NetworkId>(spawnMessage->netId);
        player->AddComponent<NetworkTransform>();
        networkId->clientAuthorityId = spawnMessage->clientAuthorityId;
        player->transform->SetWorldPos(spawnMessage->startPos);
      });
}

// ReSharper disable CppMemberFunctionMayBeStatic
// ReSharper disable once CppMemberFunctionMayBeConst
Math::Vector3 GameManager::GetPlayerStartPos() {
  // ReSharper restore CppMemberFunctionMayBeStatic
  static int count = 0;
  count++;
  return Math::Vector3(count, 0, 0);
}

void GameManager::LoadLevel(const std::string_view levelName) {
  levelLoadCompletePlayerCount = 0;
  NetworkManager::Instance().NetworkLoadLevel(levelName);
}

// ReSharper disable CppMemberFunctionMayBeStatic
// ReSharper disable once CppMemberFunctionMayBeConst
void GameManager::SendLevelLoadedMessage() {
  // ReSharper restore CppMemberFunctionMayBeStatic
  NetworkManager::Instance().SendMessageFromClient<LevelLoadedMessage>(
      [](LevelLoadedMessage* message) {});
  LOG_INFO(Debug::Channel::Networking, "Level loaded message sent");
}

void GameManager::RegisterClientLevelLoadedCallback() {
  NetworkManager::Instance().RegisterServerCallback<LevelLoadedMessage>(
      [this](int clientIndex, yojimbo::Message* inMessage) {
        auto* message = reinterpret_cast<LevelLoadedMessage*>(inMessage);
        levelLoadCompletePlayerCount++;
        LOG_INFO(Debug::Channel::Networking,
                 "%d/%d players has finished level loading",
                 levelLoadCompletePlayerCount, playerCount);

        if (levelLoadCompletePlayerCount == playerCount) {
          NetworkManager::Instance()
              .SendMessageFromServerToAll<AllPlayerReadyMessage>(
                  [](AllPlayerReadyMessage* message) {});
          LOG_INFO(Debug::Channel::Networking, "All player ready message sent");
        }
      });
}

void GameManager::RegisterAllPlayerReadyCallback() {
  NetworkManager::Instance().RegisterClientCallback<AllPlayerReadyMessage>(
      [this](yojimbo::Message* inMessage) { SendSpawnPlayerMessage(); });
}

void GameManager::RegisterClientConnectionCallbacks() {
  NetworkManager::Instance().RegisterClientConnectedCallback(
      [this](ClientInfo info) {
        playerCount++;
        LOG_INFO(Debug::Channel::Networking, "A player joined, count: %d",
                 playerCount);
      });

  NetworkManager::Instance().RegisterClientDisconnectedCallback(
      [this](ClientInfo info) {
        playerCount--;
        LOG_INFO(Debug::Channel::Networking, "A player left, count: %d",
                 playerCount);
      });
}
