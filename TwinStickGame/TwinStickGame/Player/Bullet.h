/*
 * Copyright (c) 2018 Isetta
 */
#pragma once
#include <IsettaEngine.h>

using namespace Isetta;

DEFINE_COMPONENT(Bullet, Component, true)
public:
void Initialize(const Math::Vector3& pos, const Math::Vector3& dir,
                float speed);
void Update() override;

private:
Math::Vector3 dir;
float speed = 0.f;

DEFINE_COMPONENT_END(Bullet, Component)
