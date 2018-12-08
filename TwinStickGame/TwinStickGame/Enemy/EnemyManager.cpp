/*
 * Copyright (c) 2018 Isetta
 */
#include <IsettaEngine.h>

#include "Enemy/Enemy.h"
#include "Enemy/EnemyManager.h"
#include "Networking/NetworkMessages.h"

using namespace Isetta;

EnemyManager* EnemyManager::instance = nullptr;

void EnemyManager::Awake() {
  instance = this;
  enemyPool.Resize(enemyPoolCount, nullptr);

  NetworkManager::Instance().RegisterClientCallback<RespawnEnemyMessage>(
      [this](yojimbo::Message* inMessage) {
        if (NetworkManager::Instance().IsHost()) return;

        auto* message = reinterpret_cast<RespawnEnemyMessage*>(inMessage);
        Enemy* enemy = enemyPool[message->enemyIndex];
        enemy->entity->SetActive(true);
        enemy->transform->SetWorldPos(message->spawnPos);
        enemy->Reanimate();
      });

  NetworkManager::Instance().RegisterClientCallback<InitializeEnemyMessage>(
      [this](yojimbo::Message* inMessage) {
        if (NetworkManager::Instance().IsHost()) return;

        auto* message = reinterpret_cast<InitializeEnemyMessage*>(inMessage);

        auto* enemyEntity = Entity::Instantiate("Enemy");
        auto* enemy = enemyEntity->AddComponent<Enemy>();
        enemy->enemyIndex = message->index;
        enemyEntity->AddComponent<NetworkId>(message->networkId);
        enemyEntity->AddComponent<NetworkTransform>();
        enemyEntity->SetActive(false);
        enemyPool[message->index] = enemy;
      });
}

void EnemyManager::Update() {
  if (NetworkManager::Instance().IsHost()) {
    spawnCooldown -= Time::GetDeltaTime();
    if (spawnCooldown <= 0.f) {
      SpawnEnemy();
      spawnCooldown += spawnInterval;
    }
  }
}

void EnemyManager::InitializeEnemies() {
  for (int i = 0; i < enemyPoolCount; ++i) {
    auto* enemyEntity = Entity::Instantiate("Enemy");
    auto* enemy = enemyEntity->AddComponent<Enemy>();
    enemy->enemyIndex = i;
    auto* networkId = enemyEntity->AddComponent<NetworkId>();
    int netId = networkId->id;
    enemyEntity->AddComponent<NetworkTransform>();
    enemyEntity->SetActive(false);
    enemyPool[i] = enemy;

    NetworkManager::Instance()
        .SendMessageFromServerToAll<InitializeEnemyMessage>(
            [netId, enemy](InitializeEnemyMessage* message) {
              message->networkId = netId;
              message->index = enemy->enemyIndex;
            });
  }
}

int EnemyManager::GetAvailableIndex() {
  for (int i = nextIndex; i < enemyPoolCount + nextIndex; ++i) {
    Enemy* enemy = enemyPool[i % enemyPoolCount];
    if (!enemy->entity->GetActive()) {
      nextIndex = i % enemyPoolCount + 1;
      return i % enemyPoolCount;
    }
  }
  return -1;
}

void EnemyManager::SpawnEnemy() {
  int index = GetAvailableIndex();
  if (index == -1) return;

  Math::Vector3 spawnPos = GetSpawnEnemyPos();

  Enemy* enemy = enemyPool[index];
  enemy->entity->SetActive(true);
  enemy->transform->SetWorldPos(spawnPos);
  enemy->Reanimate();

  NetworkManager::Instance().SendMessageFromServerToAll<RespawnEnemyMessage>(
      [index, spawnPos](RespawnEnemyMessage* message) {
        message->spawnPos = spawnPos;
        message->enemyIndex = index;
      });
}

Math::Vector3 EnemyManager::GetSpawnEnemyPos() {
  auto generator =
      Math::Random::GetRandomGenerator(0, spawnPositions.Size() - 1);
  auto pos = spawnPositions[generator.GetValue()] +
             Math::Vector3{Math::Random::GetRandom01() - 0.5f, 0,
                           Math::Random::GetRandom01() - 0.5f};
  return pos;
}
