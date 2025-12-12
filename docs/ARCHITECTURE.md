# Code Architecture

This document describes the structure and organization of the Minesweeper codebase.

## Project Structure

```
Minesweeper-SDL-CMake/
├── CMakeLists.txt          # Build configuration
├── .clang-format           # Code style configuration
├── README.md               # Project overview
├── cmake/                  # CMake find modules
│   ├── FindSDL2.cmake
│   ├── FindSDL2_image.cmake
│   ├── FindSDL2_mixer.cmake
│   └── FindSDL2_ttf.cmake
├── docs/                   # Documentation
│   ├── ARCHITECTURE.md     # This file
│   ├── BUILDING.md         # Build instructions
│   ├── CHANGELOG.md        # Version history
│   ├── CONTRIBUTING.md     # Contribution guidelines
│   └── GAMEPLAY.md         # User guide
├── src/                    # Source code
│   ├── main.cpp            # Entry point and game loop
│   ├── Logic.cpp/.hpp      # Game logic and input handling
│   ├── Texture.cpp/.hpp    # SDL texture wrapper
│   ├── Variables.cpp/.hpp  # Global state and constants
│   ├── StartScreen.cpp/.hpp# Menu system
│   ├── Clock.cpp/.hpp      # Timer and high scores
│   ├── Images/             # Game sprites and graphics
│   ├── Sound/              # Audio files
│   └── Font/               # TTF fonts
└── SDL2/                   # Windows SDL2 libraries (optional)
```

## Source Files

### main.cpp
Entry point containing:
- SDL initialization and cleanup
- Main game loop with frame limiting
- Window and renderer creation
- Resource loading/unloading
- High-level game state management

Key functions:
- `loadMedia()` - Load textures, fonts, sounds
- `close()` - Cleanup resources
- `main()` - Game loop and event handling

### Logic.hpp / Logic.cpp
Core game logic:
- `Button` class - Represents a clickable cell
- `createBoard()` - Generate mine layout
- `reveal()` - Open cells recursively
- `handleLeftClick()` / `handleRightClick()` - Input processing
- `relocateMine()` - First-click safety

### Texture.hpp / Texture.cpp
SDL texture wrapper class:
- `loadFromFile()` - Load image as texture
- `loadFromRenderedText()` - Render text to texture
- `render()` - Draw texture with optional clipping
- Dimension getters and resource management

### Variables.hpp / Variables.cpp
Global state and constants:
- Screen dimensions and difficulty settings (`constexpr`)
- Color definitions
- SDL objects (window, renderer, fonts)
- Game state variables (board, flags, game over state)
- Sound effect references

### StartScreen.hpp / StartScreen.cpp
Menu system:
- `showMenu()` - Main menu (New Game / Exit)
- `showGameMode()` - Difficulty selection
- `showGenericMenu()` - Reusable menu renderer

### Clock.hpp / Clock.cpp
Timer and scoring:
- `Clock` class - Game timer with start/stop/pause
- `loadHighScores()` / `saveHighScores()` - Persistence
- `checkAndUpdateHighScore()` - Record new best times

## Data Structures

### Game Boards

Two 2D vectors represent the game state:

```cpp
std::vector<std::vector<int>> board;   // Actual mine layout (hidden)
std::vector<std::vector<int>> sBoard;  // Player-visible state
```

### Cell States (title enum)

```cpp
enum title {
    BLANK,          // 0 - Empty cell
    // 1-8         // Number of adjacent mines
    MINE = 9,       // Contains a mine
    COVER,          // 10 - Unopened
    FLAG,           // 11 - Flagged by player
    QUESTION        // 12 - Question mark
};
```

### Button Class

```cpp
class Button {
    SDL_Point position;     // Screen coordinates
    int currentSprite;      // Visual state

    void setPosition(int x, int y);
    void handleEvent(SDL_Event *e, int i, int j);
    void render(int i, int j);
};
```

## Game Flow

```
┌─────────────┐
│   Start     │
└──────┬──────┘
       │
┌──────▼──────┐
│  Main Menu  │◄────────────┐
└──────┬──────┘             │
       │                    │
┌──────▼──────┐             │
│  Select     │             │
│  Difficulty │             │
└──────┬──────┘             │
       │                    │
┌──────▼──────┐             │
│  Create     │             │
│  Board      │             │
└──────┬──────┘             │
       │                    │
┌──────▼──────┐             │
│  Game Loop  │             │
│  - Render   │             │
│  - Input    │             │
│  - Update   │             │
└──────┬──────┘             │
       │                    │
   ┌───┴───┐                │
   ▼       ▼                │
┌─────┐ ┌─────┐             │
│ Win │ │Lose │             │
└──┬──┘ └──┬──┘             │
   │       │                │
   └───┬───┘                │
       │                    │
   ┌───┴───┐                │
   ▼       ▼                │
  [S]    [ESC]──────────────┘
Restart
```

## SDL2 Libraries Used

| Library | Purpose |
|---------|---------|
| SDL2 | Core windowing, rendering, events |
| SDL2_image | PNG/JPG image loading |
| SDL2_ttf | TrueType font rendering |
| SDL2_mixer | Audio playback |

## Constants Reference

Key constants defined in `Variables.hpp`:

```cpp
// Frame timing
constexpr int FPS = 24;
constexpr int frameDelay = 1000 / FPS;

// Grid
constexpr int CELL_SIZE = 32;

// Difficulty presets
constexpr int EASY_ROWS = 9, EASY_COLS = 9, EASY_MINES = 10;
constexpr int MEDIUM_ROWS = 16, MEDIUM_COLS = 16, MEDIUM_MINES = 40;
constexpr int HARD_ROWS = 16, HARD_COLS = 30, HARD_MINES = 99;
```

## Extending the Code

### Adding a New Difficulty
1. Add constants in `Variables.hpp` (rows, cols, mines, screen size)
2. Add enum value to `gameModeSelect`
3. Add case in `showGameMode()` (StartScreen.cpp)
4. Add case in main game loop (main.cpp)
5. Add high score slot in `Clock.cpp`

### Adding New Cell Types
1. Add value to `title` enum in `Variables.hpp`
2. Update `BUTTON_SPRITE_TOTAL` constant
3. Add sprite to sprite sheet
4. Update `spriteClips` initialization
5. Handle in `reveal()` and click handlers
