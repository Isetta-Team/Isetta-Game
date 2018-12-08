/*
 * Copyright (c) 2018 Isetta
 */
#include <IsettaEngine.h>

#include "Consts.h"
#include "Damageable.h"
#include "Enemy/EnemyManager.h"
#include "Enemy/Enemy.h"
#include "Gameplay/EntityFactory.h"
#include "Gameplay/GameManager.h"
#include "Menu/ColorScheme.h"
#include "Networking/NetworkMessages.h"
#include "Player/LightController.h"

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
  RegisterHealthCallbacks();
  RegisterGameOverCallback();
}

void GameManager::RegisterGameOverCallback() {
  NetworkManager::Instance().RegisterClientCallback<GameOverMessage>(
      [this](yojimbo::Message* inMessage) { isGameOver = true; });
}

void GameManager::DrawGUI() {
  if (isGameOver) {
    RectTransform rect{{0, -100, 0, 0}, GUI::Pivot::Center, GUI::Pivot::Center};
    GUI::Text(
        rect, "GAME OVER!",
        GUI::TextStyle{ColorScheme::NEON_BLUE, Consts::TITLE_SIZE, "Neon"});
  } else {
    float x = 30, y = 60;
    for (PlayerController* player : players) {
      if (player != nullptr) {
        auto* health = player->entity->GetComponent<Damageable>();
        RectTransform rect{{x, y, 0, 0}};

        rect.pivot = GUI::Pivot::Left;

        auto name = player->entity->GetName();
        GUI::Text(rect, Util::StrFormat("%s:", name.c_str()),
                  GUI::TextStyle{Consts::MID_SIZE, "Neon"});

        rect.pivot = GUI::Pivot::Left;
        rect.rect.x += 130.f;

        const float scale = 3.f;
        rect.rect.width = scale * health->GetMaxHealth();
        auto width = rect.rect.width;

        if (player->isAlive) {
          rect.rect.height = 30.f;
          GUI::Draw::RectFilled(rect,
                                Color{187.f / 255, 187.f / 255, 187.f / 255});

          rect.rect.width = scale * health->GetHealth();
          GUI::Draw::RectFilled(rect,
                                Color{109.f / 255, 205.f / 255, 116.f / 255});
        } else {
          GUI::Text(rect, "Dead!", GUI::TextStyle{Consts::MID_SIZE, "Neon"});
        }
        rect.rect.x += width + 5;
        rect.rect.height = rect.rect.width = 0;
        GUI::Text(rect, Util::StrFormat("%.0f", player->GetScore()),
                  GUI::TextStyle{Consts::MID_SIZE, "Neon"});
        y += 35;
      }
    }
  }
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

        Entity* lightEntity{Entity::Instantiate("Light")};
        lightEntity->AddComponent<LightComponent>();
        lightEntity->AddComponent<LightController>(player);

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

        Entity* lightEntity{Entity::Instantiate("Light")};
        lightEntity->AddComponent<LightComponent>();
        lightEntity->AddComponent<LightController>(player);

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

void GameManager::RegisterHealthCallbacks() {
  NetworkManager::Instance().RegisterClientCallback<PlayerDamageMessage>(
      [this](yojimbo::Message* inMessage) {
        auto* message = reinterpret_cast<PlayerDamageMessage*>(inMessage);
        auto* damageable =
            GetPlayer(message->playerIndex)->entity->GetComponent<Damageable>();
        ASSERT(damageable);
        damageable->DealDamage(-1, message->damage);
      });
}

// server only
void GameManager::NotifyPlayerDied(int playerIndex) {
  deadPlayerCount++;
  if (deadPlayerCount == playerCount) {
    NetworkManager::Instance().SendMessageFromServerToAll<GameOverMessage>(
        [](GameOverMessage* message) {});
  }
}

Math::Vector3 GameManager::GetPlayerStartPos() {
  static int count = 0;
  count++;
  return Math::Vector3(-27 + count, 0, 21);
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
      });
}
