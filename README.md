# :heavy_check_mark:  Gas Simulation
---
## :file_folder: **Folders**
- **.vscode/** contains VSCode launch settings
- **bin/** contains source code

## :stars: Dependencies
- [GLFW](https://www.glfw.org/) 3.3.2
- [OpenGL](https://www.opengl.org/) 3.3

### :bookmark_tabs: GLFW Setup VSCode (Windows)
1. [Download](https://sourceforge.net/projects/mingw-w64/files/Toolchains%20targetting%20Win32/Personal%20Builds/mingw-builds/installer/mingw-w64-install.exe/download) and install MinGW to the default directory
2. [Download](https://www.glfw.org/download.html) GLFW Windows binaries
3. Copy **include** and **lib-mingw-w64** directories to the root folder

> *If it doesn't work, try to delete **libglfw3.a** and **libglfw3dll.a** from **lib-mingw-w64***

### :bookmark_tabs: GLFW Setup GCC (OS X)
1. brew install glew
2. compile with "g++ main.cpp -framework OpenGL -lglfw"

![GitHub](https://img.shields.io/github/license/OwlCodR/gas-simulation) ![GitHub last commit](https://img.shields.io/github/last-commit/OwlCodr/gas-simulation) ![GitHub top language](https://img.shields.io/github/languages/top/OwlCodR/gas-simulation) 

![GitHub tag (latest by date)](https://img.shields.io/github/v/tag/OwlCodR/gas-simulation)
