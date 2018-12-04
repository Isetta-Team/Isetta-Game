/*
 * Copyright (c) 2018 Isetta
 */
#pragma once
#include <IsettaEngine.h>

using namespace Isetta;

DEFINE_COMPONENT(HitscanTest, Component, true)
void Start() override;
void Update() override;
void GuiUpdate() override;

private:
class Hitscan* hitscan;
DEFINE_COMPONENT_END(HitscanTest, Component)