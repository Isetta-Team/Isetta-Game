/*
 * Copyright (c) 2018 Isetta
 */
#pragma once
#include <map>
#include "Core/Geometry/Ray.h"
#include "Scene/Component.h"

using namespace Isetta;

struct HitscanProps {
  float range = 10;
  float speed = 10;
  int damage = 2;
  bool piercing = false;
};

struct HitscanShot {
  HitscanShot(Ray inRay);

  Ray ray;
  float travel = 0;
  HitscanProps* props = nullptr;

  bool operator==(const HitscanShot& rhs);
};

BEGIN_COMPONENT(Hitscan, Component, true)
void Update() override;

HitscanProps properties;
std::list<HitscanProps> shotProps;
std::unordered_map<HitscanProps*, int> propsReferenceCounts;
bool propertiesHaveChanged = true;

float cooldown = .1;
float cooldownTimer = 0;
std::list<HitscanShot> shots;

public:
Hitscan() = default;
Hitscan(float range, float rate, float speed, int damage);
void Fire(Math::Vector3 origin, Math::Vector3 direction);
END_COMPONENT(Hitscan, Component)