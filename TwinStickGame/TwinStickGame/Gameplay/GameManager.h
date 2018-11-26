/*
 * Copyright (c) 2018 Isetta
 */
#pragma once
#include "Scene/Component.h"
#include <Core/Config/CVar.h>

using namespace Isetta;

BEGIN_COMPONENT(GameManager, Component, true)
public:
struct GameConfig {
  CVarString playerName {"player_name", "Player"};
};

static GameManager& Instance();
inline static GameConfig gameConfig;
void Awake() override;
void Update() override;

private:
inline static GameManager* instance;

END_COMPONENT(GameManager, Component)