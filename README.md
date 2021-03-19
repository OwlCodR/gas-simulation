# :heavy_check_mark:  Gas Simulation
---
## :file_folder: **Folders**
- **.vscode/** contains VSCode launch settings
- **bin/** contains source code

## :stars: Dependencies
- [GLFW](https://www.glfw.org/) 3.3.2
- [GLEW](http://glew.sourceforge.net/) 2.1.0
- [GLM](http://glm.g-truc.net/0.9.5/index.html) 0.9.5.4
- [OpenGL](https://www.opengl.org/) 3.3
- [Assimp](http://assimp.org/index.php) 5.0.1

### :bookmark_tabs: Libraries Setup on VSCode (Windows)
1. [Download](https://sourceforge.net/projects/mingw-w64/files/Toolchains%20targetting%20Win32/Personal%20Builds/mingw-builds/installer/mingw-w64-install.exe/download) and install MinGW to the default directory
2. [Download](https://www.glfw.org/download.html) GLFW Windows binaries
3. Copy **include** to the root folder and copy **glfw3.dll** to the **lib** folder
4. [Download](https://sourceforge.net/projects/glew/files/glew/2.1.0/glew-2.1.0-win32.zip/download) GLEW Windows binaries
5. Copy **include** to the root folder and copy **glew32.dll** to the **lib** folder
6. [Download](https://github.com/g-truc/glm/releases/download/0.9.9.8/glm-0.9.9.8.zip) GLM Windows binaries
7. Copy **glm/glm/..** directory to the **include** folder

### :bookmark_tabs: Libraries Setup on VSCode (Linux)
1. Execute in terminal ```sudo apt install libglfw3-dev libglew-dev libglm-dev assimp-utils```
2. Modify **.vscode/tasks.json**:
```json
{
  "version": "2.0.0",
  "tasks": [
    {
      "type": "shell",
      "label": "g++ build active file",
      "command": "/usr/bin/g++",
      "args": ["-g", "${file}", "-o", "${workspaceFolder}/debug/${fileBasenameNoExtension}", "-lglfw", "-lGLEW", "-lGL"],
      "options": {
        "cwd": "/usr/bin"
      },
      "problemMatcher": ["$gcc"],
      "group": {
        "kind": "build",
        "isDefault": true
      }
    }
  ]
}
```
3. Create **debug/** folder
4. Build with ```Ctrl+Shift+B```
5. Modify **.vscode/launch.json**:
```json
{
  "version": "0.2.0",
  "configurations": [
    {
      "name": "g++ build and debug active file",
      "type": "cppdbg",
      "request": "launch",
      "program": "${workspaceFolder}/debug/${fileBasenameNoExtension}",
      "args": [],
      "stopAtEntry": false,
      "cwd": "${workspaceFolder}",
      "environment": [],
      "externalConsole": false,
      "MIMode": "gdb",
      "setupCommands": [
        {
          "description": "Enable pretty-printing for gdb",
          "text": "-enable-pretty-printing",
          "ignoreFailures": true
        }
      ],
      "preLaunchTask": "g++ build active file",
      "miDebuggerPath": "/usr/bin/gdb"
    }
  ]
}
```
6. Run with ```F5```

### :bookmark_tabs: GLFW and GLEW Setup GCC (OS X)
1. ```brew install glfw3```
2. ```brew install glew```
3. Compile with ```g++ main.cpp -framework OpenGL -lglfw -lglew```

![GitHub](https://img.shields.io/github/license/OwlCodR/gas-simulation) ![GitHub last commit](https://img.shields.io/github/last-commit/OwlCodr/gas-simulation) ![GitHub top language](https://img.shields.io/github/languages/top/OwlCodR/gas-simulation) 

![GitHub tag (latest by date)](https://img.shields.io/github/v/tag/OwlCodR/gas-simulation)
