#include "TestComponent.h"
#include <IsettaEngine.h>

void TestComponent::Update() {
  plane.UpdateRoute();
  // plane.DebugDisplay();
}
