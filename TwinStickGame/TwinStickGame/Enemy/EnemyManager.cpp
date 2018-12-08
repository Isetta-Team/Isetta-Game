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
        enemy->transform->SetLocalScale(message->localScale);
        enemy->enemyIndex = message->index;
        enemyEntity->AddComponent<NetworkId>(message->networkId);
        enemyEntity->AddComponent<NetworkTransform>();
        enemyEntity->SetActive(false);
        enemyPool[message->index] = enemy;
      });

  if (NetworkManager::Instance().IsHost()) {
    plane =
        Nav2DPlane(Math::Rect{-75, -25, 100, 100}, Math::Vector2Int{75, 75});
    plane.AddObstacle(Nav2DObstacle(
        {{-53.f, -7.f}, {-1.f, -7.f}, {-1, 11},  {17, 12},  {17, 23},
         {-1, 23},      {-1, 24},     {-1, 25},  {-1, 26},  {-1, 30},
         {-1, 41},      {-25, 41},    {-25, 59}, {-30, 59}, {-44, 59},
         {-45, 59},     {-46, 59},    {-48, 59}, {-48, 50}, {-48, 49},
         {-48, 48},     {-48, 47},    {-65, 47}, {-65, 30}, {-53, 30},
         {-53, -7}}));
  }
}

void EnemyManager::Update() {
  if (NetworkManager::Instance().IsHost()) {
    spawnCooldown -= Time::GetDeltaTime();
    if (spawnCooldown <= 0.f) {
      SpawnEnemy();
      spawnCooldown += spawnInterval;
    }
    plane.UpdateRoute();
  }
}

void EnemyManager::AddTarget(Transform* transform) {
  plane.AddTarget(transform);
}

void EnemyManager::RemoveTarget(Transform* transform) {
  plane.RemoveTarget(transform);
}

void EnemyManager::InitializeEnemies() {
  for (int i = 0; i < enemyPoolCount; ++i) {
    auto* enemyEntity = Entity::Instantiate("Enemy");
    enemyEntity->transform->SetLocalScale(Math::Vector3::one *
                                          (Math::Random::GetRandom01() + 1));
    auto* enemy = enemyEntity->AddComponent<Enemy>();
    enemy->enemyIndex = i;
    auto* networkId = enemyEntity->AddComponent<NetworkId>();
    int netId = networkId->id;
    enemyEntity->AddComponent<NetworkTransform>();
    enemyEntity->SetActive(false);
    enemyPool[i] = enemy;
    enemy->agent = enemyEntity->AddComponent<Nav2DAgent>(&plane);

    NetworkManager::Instance()
        .SendMessageFromServerToAll<InitializeEnemyMessage>(
            [netId, enemy](InitializeEnemyMessage* message) {
              message->networkId = netId;
              message->index = enemy->enemyIndex;
              message->localScale = enemy->transform->GetLocalScale();
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
