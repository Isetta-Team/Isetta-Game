/*
 * Copyright (c) 2018 Isetta
 */
#pragma once
#include <Core/Math/Math.h>

using namespace Isetta;

class InputManager {
 public:
  static Math::Vector2 GetMovementInput();
  static Math::Vector2 GetShootInput();
};