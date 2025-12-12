# Building Minesweeper

This document provides cross-platform build instructions for the Minesweeper game.

## Prerequisites

### All Platforms
- **CMake** 3.19 or higher: [Download](https://cmake.org/download/)
- **C++11 compatible compiler**

### Windows
- **Visual Studio Build Tools 2019** or later: [Download](https://visualstudio.microsoft.com/downloads/)
- **SDL2 libraries** (included in repository under `SDL2/` folder)

### Linux
Install SDL2 development libraries:
```bash
# Ubuntu/Debian
sudo apt-get install libsdl2-dev libsdl2-image-dev libsdl2-ttf-dev libsdl2-mixer-dev

# Fedora
sudo dnf install SDL2-devel SDL2_image-devel SDL2_ttf-devel SDL2_mixer-devel

# Arch Linux
sudo pacman -S sdl2 sdl2_image sdl2_ttf sdl2_mixer
```

### macOS
Install SDL2 using Homebrew:
```bash
brew install sdl2 sdl2_image sdl2_ttf sdl2_mixer
```

## Building

### Option 1: Command Line (All Platforms)

```bash
# Clone the repository
git clone https://github.com/hanzomaster/Minesweeper-SDL-CMake.git
cd Minesweeper-SDL-CMake

# Create build directory
mkdir build
cd build

# Configure and build
cmake ..
cmake --build .
```

For Release builds:
```bash
cmake -DCMAKE_BUILD_TYPE=Release ..
cmake --build . --config Release
```

### Option 2: VSCode with CMake Tools (Windows)

1. Install [VSCode](https://code.visualstudio.com/download)
2. Install extensions:
   - [CMake](https://marketplace.visualstudio.com/items?itemName=twxs.cmake)
   - [CMake Tools](https://marketplace.visualstudio.com/items?itemName=ms-vscode.cmake-tools)
3. Open the project folder in VSCode
4. Press `Ctrl+Shift+P` and select "CMake: Configure"
5. Select "Visual Studio Build Tools 2019 Release - amd64" as the kit
6. Click the Build button in the status bar

### Option 3: CMake GUI (Windows)

1. Open CMake GUI (`cmake-gui`)
2. Set "Where is the source code" to the project directory
3. Set "Where to build the binaries" to a `build` subdirectory
4. Click "Configure" (select your compiler when prompted)
5. Click "Generate"
6. Open the generated solution in Visual Studio or build from command line

## Windows PATH Setup

If using the bundled SDL2 libraries on Windows, add the DLL path to your system PATH:

1. Open System Properties > Advanced > Environment Variables
2. Edit the `PATH` variable
3. Add: `<project-path>\SDL2\lib\x64`

Alternatively, the DLLs will be copied to the build output directory automatically.

## Output Location

After building, the executable will be located at:
- **Windows**: `build/Debug/Minesweeper.exe` or `build/Release/Minesweeper.exe`
- **Linux/macOS**: `build/Minesweeper`

Game resources (Images, Sound, Font) are automatically copied to the build directory.

## Troubleshooting

### SDL2 not found
- Ensure SDL2 development packages are installed
- On Windows, verify the `SDL2/` folder exists in the project root

### Missing DLLs on Windows
- Add SDL2 lib path to system PATH, or
- Copy DLLs from `SDL2/lib/x64/` to the executable directory

### Build errors with older compilers
- Ensure your compiler supports C++11
- Update to a newer version of Visual Studio, GCC, or Clang
