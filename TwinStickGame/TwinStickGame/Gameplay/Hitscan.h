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
  bool piercing =
      false;  // TODO(Caleb): Make piercing not register damage every frame
  int refCount = 0;
};

struct HitscanBullet {
  HitscanBullet(Ray inRay);

  Ray ray;
  float travel = 0;
  HitscanProps* props = nullptr;

  bool operator==(const HitscanBullet& rhs);
};

BEGIN_COMPONENT(Hitscan, Component, true)
void Update() override;

HitscanProps properties;
std::list<HitscanProps> bulletProps;
bool propertiesChanged = true;

float cooldownTimer = 0;
std::list<HitscanBullet> bullets;

public:
Hitscan() = default;
Hitscan(float range, float rate, float speed, int damage);
void Fire(Math::Vector3 origin, Math::Vector3 direction);

int GetNumFired();
int GetNumProps();

float GetRange();
void SetRange(float r);
float GetSpeed();
void SetSpeed(float s);
int GetDamage();
void SetDamage(int d);
bool GetPiercing();
void SetPiercing(bool p);

float cooldown = .1;

END_COMPONENT(Hitscan, Component)