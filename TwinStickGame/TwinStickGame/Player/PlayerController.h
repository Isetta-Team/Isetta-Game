/*
 * Copyright (c) 2018 Isetta
 */
#pragma once
#include <Scene/Component.h>
#include <Core/Math/Vector3.h>

using namespace Isetta;

namespace Isetta {
class NetworkId;
}

DEFINE_COMPONENT(PlayerController, Component, true)
public:
void Awake() override;
void Start() override;
void Update() override;

private:
void RegisterNetworkCallbacks();
void Move();
void Shoot();
Math::Vector3 GetBulletPos();

float moveSpeed{15.0f};
bool isMoving{false};

float shootInterval{0.1f};
float shootCooldown{0.f};

NetworkId* networkId{nullptr};

DEFINE_COMPONENT_END(PlayerController, Component)
