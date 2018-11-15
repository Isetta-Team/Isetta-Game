/*
 * Copyright (c) 2018 Isetta
 */
#pragma once
#include "Core/Math/Matrix4.h"
#include "Horde3D/Horde3D.h"
#include "Scene/Component.h"

namespace Isetta {
class Ray;
namespace Math {
class Vector3;
class Vector2;
}  // namespace Math

BEGIN_COMPONENT(CameraComponent, Component, true)
public:
enum class Property {
  FOV,
  NEAR_PLANE,
  FAR_PLANE,
  PROJECTION,
};

explicit CameraComponent(std::string cameraName);

void OnEnable() override;
void OnDisable() override;
void OnDestroy() override;

template <Property Attr, typename T>
void SetProperty(T value);

template <Property Attr, typename T>
T GetProperty() const;

static const CameraComponent* Main() { return _main; }

Math::Matrix4 GetHordeTransform() const {
  const float* transformPtr;
  h3dGetNodeTransMats(renderNode, nullptr, &transformPtr);
  return Math::Matrix4(transformPtr);
}

Ray ScreenPointToRay(const Math::Vector2& position) const;
// TODO(all) ScreenToViewportPoint
// TODO(all) ScreenToWorldPoint
// TODO(all) ViewportPointToRay
// TODO(all) ViewportToScreenPoint
// TODO(all) ViewportToWorldPoint
// TODO(all) WorldToScreenPoint
// TODO(all) WorldToViewportPoint

private:
void UpdateH3DTransform() const;
void ResizeViewport(int width, int height);
void SetupCameraViewport() const;

static CameraComponent* _main;

static class RenderModule* renderModule;
friend class RenderModule;

float fov{};
float nearPlane{};
float farPlane{};
Math::Matrix4 projMat;

std::string name;
H3DNode renderNode;
H3DRes renderResource;
int resizeHandle;
END_COMPONENT(CameraComponent, Component)

template <CameraComponent::Property Attr, typename T>
void CameraComponent::SetProperty(T value) {
  if constexpr (Attr == Property::PROJECTION) {
    projMat = value;
    h3dSetCameraProjMat(renderNode, projMat.data);
  } else if constexpr (Attr == Property::FOV) {
    fov = value;
  } else if constexpr (Attr == Property::FAR_PLANE) {
    farPlane = value;
  } else if constexpr (Attr == Property::NEAR_PLANE) {
    nearPlane = value;
  }
  SetupCameraViewport();
}

template <CameraComponent::Property Attr, typename T>
T CameraComponent::GetProperty() const {
  if constexpr (Attr == Property::FOV) {
    return fov;
  } else if constexpr (Attr == Property::FAR_PLANE) {
    return farPlane;
  } else if constexpr (Attr == Property::NEAR_PLANE) {
    return nearPlane;
  } else if constexpr (Attr == Property::PROJECTION) {
    float projArr[16];
    h3dGetCameraProjMat(renderNode, projArr);
    return Math::Matrix4(projArr);
  } else {
    return {};
  }
}
}  // namespace Isetta
