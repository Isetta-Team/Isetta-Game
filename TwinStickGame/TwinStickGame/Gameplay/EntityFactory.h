/*
 * Copyright (c) 2018 Isetta
 */
#pragma once
#include <IsettaEngine.h>

using namespace Isetta;

class EntityFactory {
 public:
  static Entity* CreateNetworkEntity();
  static Entity* CreateDebugEntity();
  static Entity* CreatePlayer(std::string_view playerName);
};