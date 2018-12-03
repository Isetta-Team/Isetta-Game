/*
 * Copyright (c) 2018 Isetta
 */
#include "Gameplay/InputManager.h"
#include <Input/Input.h>

using namespace Isetta;

Math::Vector2 InputManager::GetMovementInput() {
  Math::Vector2 gamepadInput{Input::GetGamepadAxis(GamepadAxis::L_HORIZONTAL),
                             Input::GetGamepadAxis(GamepadAxis::L_VERTICAL)};

  // TODO(YIDI): Change to IsGamepadOn when we have it
  if (gamepadInput.Magnitude() < 0.1f) {
    return Math::Vector2{0, 1} * Input::IsKeyPressed(KeyCode::W) +
           Math::Vector2{-1, 0} * Input::IsKeyPressed(KeyCode::A) +
           Math::Vector2{0, -1} * Input::IsKeyPressed(KeyCode::S) +
           Math::Vector2{1, 0} * Input::IsKeyPressed(KeyCode::D);
  } else {
    return gamepadInput;
  }
}

Math::Vector2 InputManager::GetShootInput() {
  Math::Vector2 gamepadInput{Input::GetGamepadAxis(GamepadAxis::R_HORIZONTAL),
                             Input::GetGamepadAxis(GamepadAxis::R_VERTICAL)};

  // TODO(YIDI): Change to IsGamepadOn when we have it
  if (gamepadInput.Magnitude() < 0.1f) {
    return Math::Vector2{0, 1} * Input::IsKeyPressed(KeyCode::UP_ARROW) +
           Math::Vector2{-1, 0} * Input::IsKeyPressed(KeyCode::LEFT_ARROW) +
           Math::Vector2{0, -1} * Input::IsKeyPressed(KeyCode::DOWN_ARROW) +
           Math::Vector2{1, 0} * Input::IsKeyPressed(KeyCode::RIGHT_ARROW);
  } else {
    return gamepadInput;
  }
}
