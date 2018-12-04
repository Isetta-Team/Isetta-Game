/*
 * Copyright (c) 2018 Isetta
 */
#pragma once
#include <Core/Math/Vector3.h>
#include "Scene/Component.h"

using namespace Isetta;

DEFINE_COMPONENT(Bullet, Component, true)
public:
void Initialize(const Math::Vector3& pos, const Math::Vector3& dir);
void Update() override;

private:
Math::Vector3 dir;
float speed = 15;

DEFINE_COMPONENT_END(Bullet, Component)
