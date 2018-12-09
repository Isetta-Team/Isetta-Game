/*
 * Copyright (c) 2018 Isetta
 */
#pragma once
#include <IsettaEngine.h>

using namespace Isetta;

DEFINE_COMPONENT(BulletManager, Component, true)
public:
static BulletManager& Instance() { return *instance; }
void Awake() override;

void DeactivateBullet(int bulletIndex);

private:
void InitializeBullets();
int GetBulletIndex();
const int bulletPoolCount{100};
Array<class Bullet*> bulletPool{};
int nextIndex{0};  // predict next available index

AudioSource* audioComponent = nullptr;
AudioClip* gunshot = nullptr;

class Hitscan* hitScan{nullptr};
static BulletManager* instance;
DEFINE_COMPONENT_END(BulletManager, Component)