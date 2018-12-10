/*
 * Copyright (c) 2018 Isetta
 */
#include "OrbitFollow.h"
#include <IsettaEngine.h>

void OrbitFollow::Start() { center = transform->GetLocalPos(); }

void OrbitFollow::Update() {
  angle += 0.25f * Time::GetDeltaTime();
  float x = radius * Math::Util::Cos(angle) + center.x;
  float z = radius * Math::Util::Sin(angle) + center.z;
  transform->SetLocalPos(Math::Vector3{x, center.y, z});
  transform->LookAt(2 * transform->GetWorldPos() - lookAt);
}
