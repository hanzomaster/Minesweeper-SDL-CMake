# Minesweeper

A classic Minesweeper game built with C++ and SDL2.

## Features

- **Three difficulty levels**: Easy (9x9), Medium (16x16), Hard (30x16)
- **First-click safety**: Your first click never hits a mine
- **Question mark flags**: Mark uncertain cells with `?`
- **High score tracking**: Best times saved per difficulty
- **Sound effects** with mute toggle (press M)
- **Cross-platform**: Windows, Linux, macOS

## Quick Start

### Prerequisites
- CMake 3.19+
- C++11 compiler
- SDL2, SDL2_image, SDL2_ttf, SDL2_mixer

### Build
```bash
mkdir build && cd build
cmake ..
cmake --build .
```

See [docs/BUILDING.md](docs/BUILDING.md) for detailed platform-specific instructions.

## How to Play

| Action | Control |
|--------|---------|
| Open cell | Left click |
| Flag/Question | Right click (cycles) |
| Chord | Middle click |
| Restart | S (after game ends) |
| Menu | ESC (after game ends) |
| Mute | M |

See [docs/GAMEPLAY.md](docs/GAMEPLAY.md) for full gameplay guide.

## Documentation

- [Building](docs/BUILDING.md) - Build instructions for all platforms
- [Gameplay](docs/GAMEPLAY.md) - Controls and game mechanics
- [Architecture](docs/ARCHITECTURE.md) - Code structure for developers
- [Contributing](docs/CONTRIBUTING.md) - How to contribute
- [Changelog](docs/CHANGELOG.md) - Version history

## Screenshots

The game features a clean, classic Minesweeper interface with:
- Numbered cells indicating adjacent mines
- Flag and question mark markers
- Timer and mine counter
- Win/lose screens with high score display

## Credits

**Original Author**: Tran Tuan Thinh (20020265)
Advanced Programming Course Project (2021II_INT2215_2)

## License

MIT License - See [LICENSE](LICENSE) file for details.

---

###### tags: `Minesweeper` `C++` `SDL2` `CMake`
