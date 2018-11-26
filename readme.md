
## Setup for Visual Studio on Windows
Project Properties:
VC++ Directories > Include Directories > "myProjectPath/include"

Download the 3.2.1 release for your version visual studio here: https://github.com/glfw/glfw/releases

Set glfw linker in
Linker > General > Additional Library Directories:
e.g. lib-vc2015

Linker > Input > Additional Dependencies: opengl32.lib;glfw32.lib;

glad: https://glad.dav1d.de/