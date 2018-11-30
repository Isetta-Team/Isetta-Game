/*
 * Copyright (c) 2018 Isetta
 */
#pragma once
#include <Core/Config/CVar.h>

using namespace Isetta;

class GameManager {
 public:
  struct GameConfig {
    CVarString playerName{"player_name", "Unknown"};
  };

  static GameConfig gameConfig;

  static GameManager& Instance();
  void LoadLevel(std::string_view levelName) const;
  void RegisterLoadLevelCallback() const;
};