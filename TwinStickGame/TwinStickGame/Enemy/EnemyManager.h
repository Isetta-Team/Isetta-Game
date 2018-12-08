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
// Array<Math::Vector3> spawnPositions{
     // {-50, 0, -6}, {-64, 0, 46}, {-30, 0, 58}, {16, 0, 13}, {-2, 0, -6}};
// Array<Math::Vector3> spawnPositions{{1, 0, 0}, {2, 0, 0}, {3, 0, 0},
//                                     {4, 0, 0}, {5, 0, 0}, {6, 0, 0}};
Array<Math::Vector3> spawnPositions{{-20, 0, 14}};

Array<class Enemy*> enemyPool{};
const int enemyPoolCount{20};
static EnemyManager* instance;
DEFINE_COMPONENT_END(EnemyManager, Component)