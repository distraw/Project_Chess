# Project_Chess
2D Chess game with GUI, written in C++ and OpenGL, for term paper on subject "Object-oriented programming" on 2nd year in university.
## Run
1) Check the release tag. Select the last available release
2) Download .zip archive "Game.zip"
3) Unzip the archive
4) Open directory. Choose your desired operation system (so far MacOS and Windows are supported)
5) Run *"Chess" or "Chess.exe" (depending on your OS)

_* If running on MacOS, you should start "Chess" from the terminal in order to correctly read the configuration file. It will crash otherwise._
## Compile yourself
1) Clone the repo:
```
git clone -b release github.com/distraw/Project_Chess
```
2) Check if CMake is installed on your machine:
```
cmake --version
```
If not, you should install CMake in order to compile the project.
### MacOS
Simply run the script from the console
```
./run.bash
```
### Windows
**Project was originally fully compiled on MacOS. Described steps below are not guaranteed to produce expected result**

Project was originally setupped to compile on Windows using MinGW. In fact, you can use whatever you want (in that case you need to change CMake configuration, pay attention to `toolchain-mingw.cmake`)
1) Check if MinGW is installed:
```
gcc --version
```
If not, install MinGW
2) Configure CMake
```
cmake -B build-win -DCMAKE_TOOLCHAIN_FILE=toolchain-mingw.cmake
```
3) Compile
```
cmake --build build-win
```
## System Requirements

- **OS:** Windows 10/11, MacOS (Apple Silicon)
- **CPU:** x64/ARM processor
- **GPU:** OpenGL **3.3+** compatible
- **RAM:** 512 MB or higher   

Note: if program doesn't start, try to launch in debug mode ("Chess-debug" or "Chess-debug.exe") and check console output.