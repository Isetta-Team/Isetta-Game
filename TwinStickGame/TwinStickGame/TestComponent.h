/*
 * Copyright (c) 2018 Isetta
 */
#pragma once
#include <IsettaEngine.h>

#include <AI/Nav2DPlane.h>

using namespace Isetta;

DEFINE_COMPONENT(TestComponent, Component, true)
public:
void Update() override;
Nav2DAgent* agent;

Nav2DPlane plane;
TestComponent() : plane{Math::Rect{-75, -25, 100, 100}, Math::Vector2Int{75, 75}} {
  // plane.AddObstacle(Nav2DObstacle{Array<Math::Vector2>{

  //}});
}
DEFINE_COMPONENT_END(TestComponent, Component)