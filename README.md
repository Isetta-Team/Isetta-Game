# Isetta-Game
The sample, demo game for the IsettaEngine

# Setup Steps
To use this project as a base use git tag: [StarterProject]()

To setup a new project using the IsettaEngine:
- Create a Visual Studio Project
- Create a `.cpp` file to start the engine, copy:
    ```cpp
    #include <iostream>
    #include "EngineLoop.h"

    int main() {
        Isetta::Application::Start();
        return 0;
    }
    ```
- Download zip file of the [engine](https://github.com/Isetta-Team/Isetta-Engine/releases) (includes `.dll` and `.h`)
    - TODO: Create [release](https://help.github.com/articles/creating-releases/)
    - Extract in `.sln` directory
    - Move the `Resources` folder to the project level folder
- Project Properties:
    - Configuration Manager > Active solution platform: > <Edit...> > Click x86 > Remove
    - C/C++ (you will need a .cpp file to view this section)
        - General > Additional Includes: > Add `$(SolutionDir)Engine; $(SolutionDir)Engine\External;`
        - Language > C++ Language Standard > `ISO C++17 Standard (/std:c++17)`
    - Linker > Input > Add `$(SolutionDir)Engine\Build\*.lib;`
        - This will need to be different for `Debug` and `Release` builds (not currently setup)
    - Build Events > Pre-Build Event > Command Line > Add `XCOPY /Y /R "$(SolutionDir)Engine\Build\*.dll" "$(TargetDir)"`
- Configuration files
    - Create a `config.cfg` or copy a premade one (see Engine/Resources/Config/)
        - No `.cfg` in Engine/Resources/Config/ currently
    - Create a `user.cfg` for any other custom options
        - This file is not mandatory

## Prebuilt/Packaged Engine Levels

# Developing with the Engine
## Components
## Entities/Transforms
## Levels