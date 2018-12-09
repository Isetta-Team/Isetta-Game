/*
 * Copyright (c) 2018 Isetta
 */
#pragma once
#include <IsettaEngine.h>
#include "Level1Map.h"

using namespace Isetta;

DEFINE_LEVEL(Level1)
void Load() override;
Level1Map level1Map;
DEFINE_LEVEL_END