/*
 * Copyright (c) 2018 Isetta
 */
#include <IsettaEngine.h>

#include "Gameplay/GameManager.h"
#include "Gameplay/EntityFactory.h"
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
        player->transform->SetWorldPos(GetPlayerStartPos());
        NetworkId* networkId = player->AddComponent<NetworkId>();
        networkId->clientAuthorityId = clientIndex;

        player->AddComponent<NetworkTransform>();

        spawnMessage->netId = networkId->id;
        spawnMessage->clientAuthorityId = networkId->clientAuthorityId;
        spawnMessage->startPos = player->transform->GetWorldPos();

        players[clientIndex] = player->GetComponent<PlayerController>();
        NetworkManager::Instance()
            .SendMessageFromServerToAll<SpawnPlayerMessage>(spawnMessage);
        LOG_INFO(Debug::Channel::Networking,
                 "Spawn player message sent from sever for player (%s)",
                 spawnMessage->playerName);
      });

  NetworkManager::Instance().RegisterClientCallback<SpawnPlayerMessage>(
      [this](yojimbo::Message* inMessage) {
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
        players[spawnMessage->clientAuthorityId] =
            player->GetComponent<PlayerController>();
      });
}

Math::Vector3 GameManager::GetPlayerStartPos() {
  static int count = 0;
  count++;
  return Math::Vector3(count, 0, 0);
}

PlayerController* GameManager::GetPlayer(const int index) {
  return players[index];
}

void GameManager::LoadLevel(const std::string_view levelName) {
  levelLoadCompletePlayerCount = 0;
  NetworkManager::Instance().NetworkLoadLevel(levelName);
}

void GameManager::SendLevelLoadedMessage() {
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
                  [this](AllPlayerReadyMessage* message) {
                    message->playerCount = playerCount;
                  });
          LOG_INFO(Debug::Channel::Networking, "All player ready message sent");
        }
      });
}

void GameManager::RegisterAllPlayerReadyCallback() {
  NetworkManager::Instance().RegisterClientCallback<AllPlayerReadyMessage>(
      [this](yojimbo::Message* inMessage) {
        auto* message = reinterpret_cast<AllPlayerReadyMessage*>(inMessage);
        SendSpawnPlayerMessage();
        players.Resize(message->playerCount, nullptr);
      });
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
