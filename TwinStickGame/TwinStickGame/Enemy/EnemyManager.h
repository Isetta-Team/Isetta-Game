/*
 * Copyright (c) 2018 Isetta
 */
#pragma once
#include <IsettaEngine.h>

using namespace Isetta;

DEFINE_COMPONENT(EnemyManager, Component, true)
public:
static EnemyManager& Instance() { return *instance; }
void Awake() override;
void Update() override;

void AddTarget(Transform* transform);
void RemoveTarget(Transform* transform);

void DeactivateEnemy(int enemyIndex);
void InitializeEnemies();
class Enemy* GetEnemy(int enemyIndex) {
  return enemyPool[enemyIndex];
}

private:
int GetAvailableIndex();
int nextIndex = 0;

void SpawnEnemy();
float spawnInterval{3.f};
float spawnCooldown{3.f};

Math::Vector3 GetSpawnEnemyPos();

Nav2DPlane plane{};
Array<Math::Vector3> spawnPositions{
    {-45, 0, 1}, {-57, 0, 42}, {-31, 0, 54}, {-6.8, 0, 29}, {-26, 0, -1.3}};

Array<class Enemy*> enemyPool{};
const int enemyPoolCount{20};
static EnemyManager* instance;
DEFINE_COMPONENT_END(EnemyManager, Component)