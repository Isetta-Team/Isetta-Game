/*
 * Copyright (c) 2018 Isetta
 */
#pragma once
#include <IsettaEngine.h>
using namespace Isetta;

DEFINE_COMPONENT(OrbitFollow, Isetta::Component, false)
public:
void Start() override;
void Update() override;

OrbitFollow() = default;
OrbitFollow(float radius, const Math::Vector3& lookAt)
    : radius{radius}, lookAt{lookAt} {}

private:
const float radius = 1.f;
float angle = 0;
Math::Vector3 center;
const Math::Vector3 lookAt;
DEFINE_COMPONENT_END(OrbitFollow, Isetta::Component)