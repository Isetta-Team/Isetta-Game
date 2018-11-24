/*
 * Copyright (c) 2018 Isetta
 */
#pragma once
#include "Scene/Component.h"

using namespace Isetta;

BEGIN_COMPONENT(HitscanTest, Component, true)
void Start() override;
void Update() override;

private:
class Hitscan* hitscan;
END_COMPONENT(HitscanTest, Component)