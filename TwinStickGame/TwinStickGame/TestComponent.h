/*
 * Copyright (c) 2018 Isetta
 */
#pragma once
#include <IsettaEngine.h>

#include <AI/Nav2DPlane.h>
#include <AI/Nav2DAgent.h>

using namespace Isetta;

DEFINE_COMPONENT(TestComponent, Component, true)
public:
void Update() override;
Nav2DAgent* agent;

Nav2DPlane plane;
TestComponent()
    : plane{Math::Rect{-75, -25, 100, 100}, Math::Vector2Int{25, 25}} {
  plane.AddObstacle(Nav2DObstacle(
      {{-53.f, -7.f}, {-1.f, -7.f}, {-1, 8},   {17, 10},  {17, 23},
       {-1, 23},      {-1, 24},     {-1, 25},  {-1, 26},  {-1, 30},
       {-1, 41},      {-25, 41},    {-25, 59}, {-30, 59}, {-44, 59},
       {-45, 59},     {-46, 59},    {-48, 59}, {-48, 50}, {-50, 49},
       {-65, 49},     {-65, 30},    {-53, 28}, {-53, -7}}));
  // plane.AddObstacle(Nav2DObstacle{Array<Math::Vector2>{

  //}});
}
DEFINE_COMPONENT_END(TestComponent, Component)