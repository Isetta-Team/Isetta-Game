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
  Layers::NewLayer("Enemy");
  Collisions::SetIgnoreLayerCollision(Layers::NameToLayer("Enemy"), Layers::NameToLayer("Enemy"), true);

  enemyPool.Resize(enemyPoolCount, nullptr);

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

  NetworkManager::Instance().RegisterClientCallback<RespawnEnemyMessage>(
      [this](yojimbo::Message* inMessage) {
        if (NetworkManager::Instance().IsHost()) return;

        auto* message = reinterpret_cast<RespawnEnemyMessage*>(inMessage);
        Enemy* enemy = enemyPool[message->enemyIndex];
        enemy->entity->SetActive(true);
        enemy->transform->SetWorldPos(message->spawnPos);
        enemy->Reanimate();
      });

  NetworkManager::Instance().RegisterClientCallback<EnemyStateChangeMessage>(
      [this](yojimbo::Message* inMessage) {
        auto* message = reinterpret_cast<EnemyStateChangeMessage*>(inMessage);
        GetEnemy(message->enemyIndex)->ChangeState(message->newState);
      });

  // Initialize nav map
  if (NetworkManager::Instance().IsHost()) {
    plane =
        Nav2DPlane(Math::Rect{-75, -25, 100, 100}, Math::Vector2Int{25, 25});
    plane.AddObstacle(Nav2DObstacle(
        {{-53.f, -7.f}, {-1.f, -7.f}, {-1, 8},   {17, 10},  {17, 23},
         {-1, 23},      {-1, 24},     {-1, 25},  {-1, 26},  {-1, 30},
         {-1, 41},      {-25, 41},    {-25, 59}, {-30, 59}, {-44, 59},
         {-45, 59},     {-46, 59},    {-48, 59}, {-48, 50}, {-50, 49},
         {-65, 49},     {-65, 30},    {-53, 28}, {-53, -7}}));
  }
}

// server only
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

    enemy->agent = enemyEntity->AddComponent<Nav2DAgent>(&plane, 5, 2, 0.1, 1);
    enemy->agent->onTargetArrive.Subscribe(
        [enemy](Transform* target) { enemy->OnReachTarget(target); });

    enemyEntity->SetActive(false);
    enemyPool[i] = enemy;

    NetworkManager::Instance()
        .SendMessageFromServerToAll<InitializeEnemyMessage>(
            [netId, enemy](InitializeEnemyMessage* message) {
              message->networkId = netId;
              message->index = enemy->enemyIndex;
              message->localScale = enemy->transform->GetLocalScale();
            });
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
