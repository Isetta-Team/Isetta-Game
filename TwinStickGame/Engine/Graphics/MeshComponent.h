/*
 * Copyright (c) 2018 Isetta
 */
#pragma once
#include <string>
#include "Horde3D/Horde3D.h"
#include "Scene/Component.h"

namespace Isetta {
BEGIN_COMPONENT(MeshComponent, Component, false)
H3DNode renderNode{0};
H3DRes renderResource{0};

explicit MeshComponent(std::string_view resourceName);
~MeshComponent();

void UpdateTransform() const;

protected:
static H3DRes LoadResourceFromFile(std::string_view resourceName);

void OnEnable() override;
void OnDisable() override;
void OnDestroy() override;

friend class AnimationComponent;
friend class Entity;
friend class MemoryManager;
friend class FreeListAllocator;
friend class RenderModule;

static class RenderModule* renderModule;
END_COMPONENT(MeshComponent, Component)
}  // namespace Isetta
