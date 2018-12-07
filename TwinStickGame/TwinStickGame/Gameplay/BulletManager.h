/*
 * Copyright (c) 2018 Isetta
 */
#pragma once
#include <IsettaEngine.h>

using namespace Isetta;

DEFINE_COMPONENT(BulletManager, Component, true)
public:
void Awake() override;

private:
int bulletPoolCount{100};
class Hitscan* hitScan {nullptr};
DEFINE_COMPONENT_END(BulletManager, Component)