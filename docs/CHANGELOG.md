# Changelog

All notable changes to the Minesweeper project are documented in this file.

The format is based on [Keep a Changelog](https://keepachangelog.com/en/1.0.0/).

## [1.1.0] - 2024

### Added
- **Hard difficulty mode** (30x16 grid, 99 mines) for expert players
- **First-click safety** - First click never hits a mine; mines relocate if needed
- **Question mark flags** - Right-click cycles: Cover → Flag → Question → Cover
- **High score system** - Best times saved per difficulty, displayed on win
- **Mute toggle** - Press 'M' to toggle sound on/off during gameplay
- **Cross-platform CMake support** - Build on Windows, Linux, and macOS
- **Comprehensive documentation** in `docs/` folder

### Fixed
- **Win condition** now matches classic Minesweeper (reveal all non-mine cells)
- **Switch fall-through bugs** in menu handling (StartScreen.cpp)
- Previously, win required flagging all mines; now just reveal all safe cells

### Changed
- **Code modernization** - Using C++11 `constexpr` for compile-time constants
- **Refactored menu code** - Generic `showGenericMenu()` reduces duplication
- **Named constants** replace magic numbers throughout codebase
- **CMake minimum version** bumped to 3.19 for modern features
- **Project renamed** from "game" to "Minesweeper" in CMake

### Developer Improvements
- Added `.clang-format` for consistent code style (Allman braces, 4-space indent)
- Conditional SDL2 paths (Windows-only) in CMakeLists.txt
- Post-build resource copying for easier debugging
- macOS bundle support in CMake

## [1.0.0] - 2021

### Initial Release
- Classic Minesweeper gameplay
- Two difficulty levels: Easy (9x9, 10 mines) and Medium (16x16, 40 mines)
- Mouse controls: left-click to reveal, right-click to flag, middle-click to chord
- Keyboard controls: 'S' to restart, 'ESC' for menu
- Sound effects and background music
- Built with SDL2, SDL2_image, SDL2_ttf, SDL2_mixer
- CMake build system
- Windows support with bundled SDL2 libraries

---

## Version History Summary

| Version | Date | Highlights |
|---------|------|------------|
| 1.1.0 | 2024 | Hard mode, first-click safety, high scores, cross-platform |
| 1.0.0 | 2021 | Initial release with Easy/Medium modes |
