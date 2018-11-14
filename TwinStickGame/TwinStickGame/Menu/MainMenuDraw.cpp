/*
 * Copyright (c) 2018 Isetta
 */
#include "MainMenuDraw.h"

// ENGINE
#include "Core/Debug/DebugDraw.h"
#include "Core/Time/Time.h"

// GAME
#include "ColorScheme.h"

void MainMenuDraw::Update() {
  const int lines = 50;
  gridPosition.z += gridSpeed * Time::GetDeltaTime();

  DebugDraw::Grid(Math::Matrix4::Translate(-gridPosition), lines,
                  ColorScheme::NEON_PURPLE);
  DebugDraw::Grid(
      Math::Matrix4::Translate(-gridPosition - lines * Math::Vector3::forward),
      lines, ColorScheme::NEON_PURPLE);
  if (gridPosition.z >= 30) gridPosition.z = 0.f;
}
