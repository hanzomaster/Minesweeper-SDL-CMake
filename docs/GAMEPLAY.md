# Gameplay Guide

## Game Objective

Clear the minefield without detonating any mines. Use the numbers revealed when opening cells to deduce mine locations and flag them.

## Difficulty Levels

| Difficulty | Grid Size | Mines | Description |
|------------|-----------|-------|-------------|
| Easy       | 9 x 9     | 10    | Good for beginners |
| Medium     | 16 x 16   | 40    | Standard challenge |
| Hard       | 30 x 16   | 99    | Expert level |

## Controls

### Mouse Controls

| Action | Description |
|--------|-------------|
| **Left Click** | Open a cell to reveal what's underneath |
| **Right Click** | Cycle through: Cover → Flag → Question Mark → Cover |
| **Middle Click** | Chord - Open all adjacent cells when flags match the number |

### Keyboard Controls

| Key | Action |
|-----|--------|
| **S** | Start a new game (same difficulty) - available after win/loss |
| **ESC** | Return to menu - available after win/loss |
| **M** | Toggle sound mute on/off |

## Game Elements

### Cell Types

| Symbol | Meaning |
|--------|---------|
| Covered (gray) | Unopened cell |
| Numbers (1-8) | Count of adjacent mines |
| Blank | No adjacent mines (auto-expands) |
| Flag | Marked as suspected mine |
| Question Mark (?) | Uncertain - for strategic marking |
| Mine | Game over if opened! |

### Number Colors

Each number has a distinct color to help identify mine counts quickly:
- **1**: Blue
- **2**: Green
- **3**: Red
- **4**: Dark Blue
- **5**: Maroon
- **6**: Cyan
- **7**: Black
- **8**: Gray

## Winning and Losing

### How to Win
- Open all cells that don't contain mines
- You do NOT need to flag all mines to win

### How to Lose
- Click on a cell containing a mine

### After Game Ends
- Press **S** to play again with the same difficulty
- Press **ESC** to return to the difficulty selection menu

## High Scores

The game tracks your best completion times for each difficulty level:
- Times are saved automatically when you win
- High scores persist between game sessions
- Displayed on the win screen

## Tips and Strategies

1. **First click is always safe** - The game ensures your first click never hits a mine

2. **Use flags sparingly** - Only flag cells you're certain contain mines

3. **Question marks for uncertainty** - Use `?` to mark cells you're unsure about

4. **Look for patterns** - Common patterns like "1-2-1" indicate specific mine placements

5. **Chording saves time** - Middle-click on numbered cells with correct flags to quickly open safe adjacent cells

6. **Corner cells** - Numbers in corners touch fewer cells, making deduction easier

7. **Start from edges** - Edge and corner cells are often easier to solve first

## Sound

The game includes sound effects for:
- Menu clicks
- Opening cells
- Placing/removing flags
- Finding mines
- Winning music

Press **M** at any time to toggle sounds on/off.
