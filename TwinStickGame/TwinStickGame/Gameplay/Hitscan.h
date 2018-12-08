/*
 * Copyright (c) 2018 Isetta
 */
#pragma once
#include <IsettaEngine.h>

using namespace Isetta;

struct HitscanProps {
  float range = 10;
  float speed = 10;
  int damage = 2;
  // TODO(Caleb): Make piercing not register damage every frame
  bool piercing = false;
  int refCount = 0;
  int playerIndex = 0;
  int bulletIndex = 0;  // bullet entity index
};

struct HitscanBullet {
  HitscanBullet(Ray inRay);

  Ray ray;
  float travel = 0;
  HitscanProps* props = nullptr;

  bool operator==(const HitscanBullet& rhs) const;
};

DEFINE_COMPONENT(Hitscan, Component, true)
void Update() override;

HitscanProps properties;
std::list<HitscanProps> bulletProps;
bool propertiesChanged = true;

std::list<HitscanBullet> bullets;

public:
Hitscan() = default;
Hitscan(float range, float speed, int damage);
void Fire(Math::Vector3 origin, Math::Vector3 direction);

int GetNumFired() const;
int GetNumProps() const;

float GetRange() const;
void SetRange(float range);
float GetSpeed() const;
void SetSpeed(float speed);
int GetDamage() const;
void SetDamage(int damage);
bool GetPiercing() const;
void SetPiercing(bool shouldPierce);
int GetPlayerIndex() const;
void SetPlayerIndex(int playerIndex);
int GetBulletIndex() const;
void SetBulletIndex(int bulletIndex);
DEFINE_COMPONENT_END(Hitscan, Component)