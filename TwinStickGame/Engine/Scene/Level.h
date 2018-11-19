/*
 * Copyright (c) 2018 Isetta
 */
#pragma once
#include <list>
#include <set>
#include <stack>
#include <string>
#include "ISETTA_API.h"

#define CREATE_LEVEL(NAME)                                                \
  class NAME : public Isetta::Level, public Isetta::LevelRegistry<NAME> { \
   public:                                                                \
    bool IsRegisteredInLevelManager() const { return registered; }        \
    static inline Isetta::Func<NAME*> CreateMethod = []() {               \
      return Isetta::MemoryManager::NewOnStack<NAME>();                   \
    };                                                                    \
    static std::string GetLevelName() { return #NAME; }                   \
    std::string GetName() const override { return #NAME; }                \
                                                                          \
   private:

#define CREATE_LEVEL_END \
  }                      \
  ;

namespace Isetta {
class ISETTA_API Level {
 private:
  std::list<class Entity*> entitiesToRemove;
  void AddComponentToStart(class Component* component);
  void StartComponents();

  void UnloadLevel();
  void Update();
  void GUIUpdate();
  void FixedUpdate();
  void LateUpdate();

  friend class Entity;
  friend class EngineLoop;
  friend class GUIModule;
  friend class LevelManager;

 protected:
  std::list<class Entity*> entities;
  std::stack<class Component*> componentsToStart;
  std::set<class Component*> componentsToDestroy;

 public:
  class Entity* levelRoot;
  Level();
  virtual ~Level() = default;

  virtual std::string GetName() const = 0;
  class Entity* GetEntityByName(const std::string&);
  class std::list<class Entity*> GetEntitiesByName(const std::string&);
  class std::list<class Entity*> GetEntities() const;

  virtual void OnLevelLoad() = 0;
  virtual void OnLevelUnload() {}

  class Entity* AddEntity(std::string name, bool entityStatic = false);
  class Entity* AddEntity(std::string name, class Entity* parent,
                          bool entityStatic = false);
};
}  // namespace Isetta
