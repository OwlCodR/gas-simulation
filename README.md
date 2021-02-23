# :heavy_check_mark:  Gas Simulation
---
## :file_folder: **Folders**
- **.vscode/** contains VSCode launch settings
- **bin/** contains source code

## :stars: Dependencies
- [GLFW](https://www.glfw.org/) 3.3.2
- [GLEW](http://glew.sourceforge.net/) 2.1.0
- [OpenGL](https://www.opengl.org/) 3.3

### :bookmark_tabs: GLFW/GLEW Setup on VSCode (Windows)
1. [Download](https://sourceforge.net/projects/mingw-w64/files/Toolchains%20targetting%20Win32/Personal%20Builds/mingw-builds/installer/mingw-w64-install.exe/download) and install MinGW to the default directory
2. [Download](https://www.glfw.org/download.html) GLFW Windows binaries
3. Copy **include** to the root folder and copy **glfw3.dll** to the **lib** folder
4. [Download](https://sourceforge.net/projects/glew/files/glew/2.1.0/glew-2.1.0-win32.zip/download) GLEW Windows binaries
5. Copy **include** to the root folder and copy **glew32.dll** to the **lib** folder

### :bookmark_tabs: GLFW and GLEW Setup GCC (OS X)
1. brew install glfw3
   brew install glew
2. compile with "g++ main.cpp -framework OpenGL -lglfw -lglew"

![GitHub](https://img.shields.io/github/license/OwlCodR/gas-simulation) ![GitHub last commit](https://img.shields.io/github/last-commit/OwlCodr/gas-simulation) ![GitHub top language](https://img.shields.io/github/languages/top/OwlCodR/gas-simulation) 

![GitHub tag (latest by date)](https://img.shields.io/github/v/tag/OwlCodR/gas-simulation)
