#include <IsettaEngine.h>

#include "TestComponent.h"

void TestComponent::Update() {
  plane.UpdateRoute();
  plane.DebugDisplay();
}
