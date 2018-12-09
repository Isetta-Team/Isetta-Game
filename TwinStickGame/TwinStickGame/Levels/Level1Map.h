/*
 * Copyright (c) 2018 Isetta
 */
#pragma once
#include <Scene/IsettaLevel.h>

using namespace Isetta;

DEFINE_LEVEL(Level1Map)
public:
void Load() override;
void LoadTestEntities();
DEFINE_LEVEL_END