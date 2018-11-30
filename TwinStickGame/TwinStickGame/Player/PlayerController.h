/*
 * Copyright (c) 2018 Isetta
 */
#pragma once
#include <Scene/Component.h>

using namespace Isetta;

namespace Isetta {
class NetworkId;
}

BEGIN_COMPONENT(PlayerController, Component, true)
public:
void Start() override;
void Update() override;

private:
void Move();
float scale{0.01f};
float moveSpeed{15.0f};
bool isMoving{false};
float lookSmooth{30.f};
NetworkId* networkId{nullptr};

END_COMPONENT(PlayerController, Component)
