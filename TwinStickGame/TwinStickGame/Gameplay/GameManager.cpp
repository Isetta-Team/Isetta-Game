/*
 * Copyright (c) 2018 Isetta
 */
#include <IsettaEngine.h>

#include "BulletManager.h"
#include "Damageable.h"
#include "Enemy/Enemy.h"
#include "Enemy/EnemyManager.h"
#include "Gameplay/EntityFactory.h"
#include "Gameplay/GameManager.h"
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
  RegisterHitEnemyCallback();
  RegisterScoreCallbacks();
}

std::string GameManager::GetPlayerName(int playerIndex) {
  return Instance().GetPlayer(playerIndex)->entity->GetName();
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
        spawnMessage->clientAuthorityId = clientIndex;
        spawnMessage->startPos = player->transform->GetWorldPos();

        players[clientIndex] = player->GetComponent<PlayerController>();
        players[clientIndex]->playerIndex = clientIndex;

        if (NetworkManager::Instance().GetClientIndex() ==
            spawnMessage->clientAuthorityId) {
          localPlayer = player->GetComponent<PlayerController>();
        }

        EnemyManager::Instance().AddTarget(player->transform);

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
        players[spawnMessage->clientAuthorityId]->playerIndex =
            spawnMessage->clientAuthorityId;

        if (NetworkManager::Instance().GetClientIndex() ==
            spawnMessage->clientAuthorityId) {
          localPlayer = player->GetComponent<PlayerController>();
        }
      });
}

void GameManager::RegisterScoreCallbacks() {
  NetworkManager::Instance().RegisterClientCallback<ScoreMessage>(
      [](yojimbo::Message* inMessage) {
        auto* message = reinterpret_cast<ScoreMessage*>(inMessage);
        Instance().GetPlayer(message->playerIndex)->Score(message->score);
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

          EnemyManager::Instance().InitializeEnemies();
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

void GameManager::RegisterHitEnemyCallback() {
  NetworkManager::Instance().RegisterClientCallback<HitEnemyMessage>(
      [](yojimbo::Message* inMessage) {
        auto* message = reinterpret_cast<HitEnemyMessage*>(inMessage);
        auto* damageable = EnemyManager::Instance()
                               .GetEnemy(message->enemyIndex)
                               ->entity->GetComponent<Damageable>();
        ASSERT(damageable != nullptr);
        damageable->DealDamage(message->playerIndex, message->damage);
        LOG_INFO(Debug::Channel::Gameplay, "%s hit %s and dealt %.3f damage",
                 Instance().GetPlayerName(message->playerIndex).c_str(),
                 damageable->entity->GetName().c_str(), message->damage);
      });
}
