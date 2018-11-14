/*
 * Copyright (c) 2018 Isetta
 */
#pragma once
#include "Core/DataStructures/Array.h"
#include "Core/IsettaAlias.h"
#include "Core/Math/Matrix4.h"
#include "Core/Math/Quaternion.h"
#include "Core/Math/Vector3.h"
#include "Horde3D/Horde3D.h"

namespace Isetta {
class ISETTA_API_DECLARE Transform {
  friend class Entity;

 public:
  // constructors
  Transform() = delete;
  explicit Transform(class Entity *const entity);
  ~Transform();

  // position
  Math::Vector3 GetWorldPos();
  Math::Vector3 GetLocalPos() const;
  void SetWorldPos(const Math::Vector3 &newWorldPos);
  void SetLocalPos(const Math::Vector3 &newLocalPos);

  void TranslateWorld(const Math::Vector3 &delta);
  void TranslateLocal(const Math::Vector3 &delta);

  // rotation
  Math::Quaternion GetWorldRot();
  Math::Quaternion GetLocalRot() const;
  Math::Vector3 GetWorldEulerAngles();
  Math::Vector3 GetLocalEulerAngles() const;
  void SetWorldRot(const Math::Quaternion &newWorldRot);
  void SetWorldRot(const Math::Vector3 &worldEulers);
  void SetLocalRot(const Math::Quaternion &newLocalRot);
  void SetLocalRot(const Math::Vector3 &localEulers);

  void RotateWorld(const Math::Vector3 &eulerAngles);
  void RotateWorld(const Math::Vector3 &axis, float angle);
  void RotateLocal(const Math::Vector3 &eulerAngles);
  void RotateLocal(const Math::Vector3 &axisWorldSpace, float angle);
  void RotateLocal(const Math::Quaternion &rotation);

  // scale
  Math::Vector3 GetWorldScale();
  Math::Vector3 GetLocalScale() const;
  void SetLocalScale(const Math::Vector3 &newScale);
  void SetWorldScale(const Math::Vector3 &newScale);

  // hierarchy
  void SetParent(Transform *const transform);
  Transform *GetParent() const { return parent; }
  Transform *GetRoot() const;

  // helper
  Math::Vector3 GetForward();
  Math::Vector3 GetUp();
  Math::Vector3 GetLeft();
  Math::Vector3 GetAxis(int i);

  // other
  void LookAt(const Math::Vector3 &target,
              const Math::Vector3 &worldUp = Math::Vector3::up);
  void LookAt(Transform &target,
              const Math::Vector3 &worldUp = Math::Vector3::up);
  class Entity *GetEntity() const {
    return entity;
  }
  inline Size GetChildCount() const { return children.Size(); }
  Transform *GetChild(U16 childIndex);
  inline std::string GetName() const;

  // utilities
  Math::Vector3 WorldPosFromLocalPos(const Math::Vector3 &localPoint);
  Math::Vector3 LocalPosFromWorldPos(const Math::Vector3 &worldPoint);
  Math::Vector3 WorldDirFromLocalDir(const Math::Vector3 &localDirection);
  Math::Vector3 LocalDirFromWorldDir(const Math::Vector3 &worldDirection);

  void ForChildren(const Action<Transform *> &action);
  void ForDescendants(const Action<Transform *> &action);

  void SetWorldTransform(const Math::Vector3 &inPosition,
                         const Math::Vector3 &inEulerAngles,
                         const Math::Vector3 &inScale);

  // more utilities
  // TODO(YIDI): Decide if they should stay here
  static void SetH3DNodeTransform(H3DNode node, Transform &transform);

  const Math::Matrix4 &GetLocalToWorldMatrix();
  const Math::Matrix4 &GetWorldToLocalMatrix();

  // iterator
  typedef Array<Transform *>::iterator iterator;
  typedef Array<Transform *>::const_iterator const_iterator;

  iterator begin() { return children.begin(); }
  const_iterator begin() const { return children.begin(); }
  iterator end() { return children.end(); }
  const_iterator end() const { return children.end(); }

  // both called by SetParent
  void AddChild(Transform *transform);
  void RemoveChild(Transform *transform);

 private:
  void RecalculateLocalToWorldMatrix();

  Math::Quaternion worldRot;  // only for query
  Math::Vector3 worldScale;   // only for query

  Math::Matrix4 localToWorldMatrix{};
  Math::Matrix4 worldToLocalMatrix{};
  Math::Vector3 localPos{Math::Vector3::zero};  // part of local storage
  Math::Quaternion localRot{
      Math::Quaternion::identity};               // part of local storage
  Math::Vector3 localScale{Math::Vector3::one};  // part of local storage

  // marked when anything local changed
  // cleared when matrix recalculated
  void SetDirty();
  bool isDirty{true};
  bool isWorldToLocalDirty{true};

  class Entity *const entity{nullptr};
  Transform *parent{nullptr};
  Array<Transform *> children;

  // union {
  Math::Vector3 axis[3];
  Math::Vector3 &left = axis[0];
  Math::Vector3 &up = axis[1];
  Math::Vector3 &forward = axis[2];
};
}  // namespace Isetta