/*
 * Copyright (c) 2018 Isetta
 */
#pragma once
#include "Scene/Component.h"

namespace Isetta {
DEFINE_COMPONENT(NetworkTestComp, Component, true)
public:
void Start() override;
DEFINE_COMPONENT_END(NetworkTestComp, Component)
}  // namespace Isetta