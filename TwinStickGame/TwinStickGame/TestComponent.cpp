#include <IsettaEngine.h>

#include "TestComponent.h"

void TestComponent::Update() {
  // plane.UpdateRoute();
#ifdef _EDITOR
  plane->DebugDraw();
#endif
}
