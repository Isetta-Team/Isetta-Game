/*
 * Copyright (c) 2018 Isetta
 */
#pragma once
#include <IsettaEngine.h>

#include <AI/Nav2DAgent.h>
#include <AI/Nav2DPlane.h>

using namespace Isetta;

DEFINE_COMPONENT(TestComponent, Component, true)
public:
void Update() override;
Nav2DAgent* agent;

Nav2DPlane* const plane;

TestComponent() = default;
TestComponent(Nav2DPlane* const plane) : plane{plane} {}
DEFINE_COMPONENT_END(TestComponent, Component)