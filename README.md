# Isetta-Game
The sample, demo game for the IsettaEngine

# Setup Steps
To use this project as a base use git tag: [StarterProject]()

To setup a new project using the IsettaEngine:
- Create a Visual Studio Project
- Create a `.cpp` file to start the engine, copy:
    ```cpp
    #include <EngineLoop.h>

    int main() {
        Isetta::Application::Start();
        return 0;
    }
    ```
- Download zip file of the [engine](https://github.com/Isetta-Team/Isetta-Engine/releases) (includes `.dll` and `.h`)
    - TODO (JACOB!): Create [release](https://help.github.com/articles/creating-releases/)
    - Extract in `.sln` directory
- Project Properties:
    - Configuration Manager > Active solution platform: > <Edit...> > Click x86 > Remove
    - Configuration Manager > Active solution configuration: > <New...> > Put "ReleaseEditor" in name > OK
    - (Make sure you do the following changes with "All Configurations" selected as Configuration)
    - Debugging > Change Working Directory to "$(TargetDir)"
    - C/C++ (you will need a .cpp file to view this section)
        - General > Additional Includes: > Add `$(SolutionDir)Engine; $(SolutionDir)Engine\External;`
        - Language > C++ Language Standard > `ISO C++17 Standard (/std:c++17)`
    - Linker > Input > Add `$(SolutionDir)Engine\Build\*.lib;`
        - This will need to be different for `Debug` and `Release` builds (not currently setup)
    - Build Events
        - Pre-Build Event > Command Line > Add `XCOPY /Y /R "$(SolutionDir)Engine\Build\*.dll" "$(TargetDir)"`
        - Post-Build Event > Command Line > Add:
        ```
        XCOPY /Y /R /S /I "$(SolutionDir)Engine\Resources\*" "$(TargetDir)Resources"
        XCOPY /Y /R /S /I "$(ProjectDir)Resources\*" "$(TargetDir)Resources"
        XCOPY /Y /R "$(ProjectDir)*.cfg" "$(TargetDir)"
        ```
- Configuration files
    - Create a `config.cfg` or copy a premade one (see Engine/Resources/Config/)
        - No `.cfg` in Engine/Resources/Config/ currently
    - Create a `user.cfg` for any other custom options
        - This file is not mandatory

## Prebuilt/Packaged Engine Levels

# Developing with the Engine
The Isetta Engine uses an entity-component-system. Assumptions of the engine:
- Coordinates are right-handed (`Vector3::left = (1, 0, 0)`)
- Matricies are row-column (`Matrix4 mat[ROW][COLUMN]`)
- When using the built `MemoryManager`, it does not protect you against yourself (in general the engine does not protect a naive user from shooting themselves in the foot)

## Entities/Transforms
Entities are the objects that persist in the level/scene that can have a parent entity and can have children entities. Entities hold components and have a transform to locate them in the world. Entities can be add to the level through the macros `Entity::Instantiate(std::string name, Entity* parent, bool isStatic)` included with `#include "Scene/Entity.h"`, and return an entity pointer. The `parent` defaults to `nullptr` which sets the entity's parent to the top level and `isStatic` defaults to `false`. Static entities cannot be translated, rotated, or scaled once the level has loaded.

Transforms hold the position, rotation, and scale information for an entity. The transformation information has local and world transformation, as well as the local axes of the entity.

```cpp
Entity* entity = Entity::Instantiate("entityName");
Transform* transform = entity->transform;
entity->AddComponent<ExampleComponent>();
```

Entities in the Isetta engine are comparable to GameObjects in Unity and Entities in Unreal.

## Components
Components in the Isetta Engine are similar to components in other engines, they should be designed for individal tasks and have minimal coupling with other components. Components cannot be standalone/instantiated in a level without being attached to an entity, done with `entity->AddComponent<COMPONENT, bool isActive = true>(Component constructor args...)`. 
- `entity` is an instantiated entity variable as shown above
- `COMPONENT` is the class name of your component to add, ie. `ExampleComponent`
- `bool isActive = true` is whether the component starts enabled/disabled and defaults to starting active
- `Component constructor args...` are the arguments to pass to the component's constructor (can be empty to use the default constructor -- a component MUST have a default constructor in addition to any other constructors)

A component is created with Isetta component macros: `DEFINE_COMPONENT(COMPONENT, PARENT, bool unique)` and `DEFINE_COMPONENT_END(COMPONENT_NAME, PARENT)`. Where:
- `COMPONENT` is the name of your new component class, ie. `ExampleComponent`
- `PARENT` is the name of the parent/base class of component, use `Component` if you have no base class
- `bool unique` is whether the component must be unique on an entity (whether an entity could have multiple of this component)
    - The unique variable does NOT mean the component is unique across the level, ie. a singleton

To create a component, create a header (.h) and cpp (.cpp) file of the name of your component:

`ExampleComponent.h`
```cpp
#pragma once
#include <Scene/Component.h>

DEFINE_COMPONENT(ExampleComponent, Component, true)
private:
// Private variables of your component
public:
// A component MUST have a default constructor
ExampleComponent() = default;

// Awake is called once, immediately when the component is first created and enabled
void Awake() override;
// Start is called once, on the first update frame after the component is created and enabled
void Start() override;
// OnEnable is called immediately each time the component becomes active, including after creation
void OnEnable() override;
// OnDisable is called immediately each time the component becomes inactive
void OnDisable() override;
// Update is called each frame (variable delta time)
void Update() override;
// GuiUpdate is called each frame (variable delta time), GUI can only be called in GuiUpdate
void GuiUpdate() override;
// LateUpdate is called each frame (variable delta time)
void LateUpdate() override;
// FixedUpdate is called on fixed time (constant delta time)
void FixedUpdate() override;
// OnDestroy is called once when the component is destroyed
void OnDestroy() override;

DEFINE_COMPONENT_END(ExampleComponent, Component)
```

The cpp file then contains the definitions for each of these functions. Not all functions need to be defined, if not overriden, the function update will run faster.

Here are empty template of component header to copy:
```cpp
#pragma once
#include <Scene/Component.h>

DEFINE_COMPONENT(COMPONENT_NAME, Component, true)
private:
public:
COMPONENT_NAME() = default;
DEFINE_COMPONENT_END(COMPONENT_NAME, Component)
```

## Levels

`LEVEL_NAME.h`
```cpp
#pragma once
#include <Scene/IsettaLevel.h>
#include <Scene/Level.h>

DEFINE_LEVEL(LEVEL_NAME)
void Load() override;
void OnLevelUnload() override;
DEFINE_LEVEL_END
```

`LEVEL_NAME.cpp`
```cpp
#include "LEVEL_NAME.h"

// IsettaCore not necessarily needed, holds a number of useful header files
#include <Core/IsettaCore.h>
#include <Graphics/CameraComponent.h>

void LEVEL_NAME::Load() {
    // Level NEEDS a camera
    Entity* cameraEntity = Entity::Instantiate("Camera");
    cameraEntity->AddComponent<CameraComponent>();
    cameraEntity->SetTransform(Math::Vector3{0, 5, 10}, Math::Vector3{-15, 0, 0},
                             Math::Vector3::one);
}

void LEVEL_NAME::OnLevelUnload() {
    // Anything you might need to do on the level unloading
    // Entity's will be destructed/destroyed on actual level unload
}
```
