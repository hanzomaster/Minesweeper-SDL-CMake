# Contributing to Minesweeper

Thank you for your interest in contributing to this project! This document provides guidelines for contributing.

## Getting Started

1. Fork the repository
2. Clone your fork locally
3. Set up the development environment (see [BUILDING.md](BUILDING.md))
4. Create a feature branch from `main`

## Development Setup

### Prerequisites
- CMake 3.19+
- C++11 compatible compiler
- SDL2 and related libraries (see [BUILDING.md](BUILDING.md))

### Code Style

This project uses `.clang-format` for consistent code formatting:

- **Indentation**: 4 spaces (tabs)
- **Brace Style**: Allman (braces on new lines)
- **Line Length**: 120 characters max
- **Pointer Alignment**: Right (`int *ptr`)

Format your code before committing:
```bash
# Format a single file
clang-format -i src/filename.cpp

# Format all source files
find src -name "*.cpp" -o -name "*.hpp" | xargs clang-format -i
```

### Building for Development

```bash
mkdir build && cd build
cmake -DCMAKE_BUILD_TYPE=Debug ..
cmake --build .
```

## Making Changes

### Branch Naming

Use descriptive branch names:
- `feature/add-custom-difficulty`
- `fix/mine-placement-bug`
- `docs/update-readme`

### Commit Messages

Write clear, concise commit messages:
- Use present tense ("Add feature" not "Added feature")
- Use imperative mood ("Fix bug" not "Fixes bug")
- Keep first line under 50 characters
- Add details in body if needed

Examples:
```
Add question mark flag cycling

Allow players to cycle through Cover -> Flag -> Question -> Cover
when right-clicking cells, providing a way to mark uncertain cells.
```

### Code Guidelines

1. **Keep it simple** - Avoid over-engineering
2. **Document complex logic** - Add comments where intent isn't obvious
3. **Use constants** - Prefer named constants over magic numbers
4. **Handle errors gracefully** - Check SDL function return values
5. **Test your changes** - Play the game and verify functionality

### What to Avoid

- Breaking existing functionality
- Adding dependencies without discussion
- Large refactors without prior approval
- Platform-specific code without alternatives

## Submitting Changes

### Pull Request Process

1. Ensure your code compiles without warnings
2. Test the game thoroughly (all difficulty levels)
3. Update documentation if needed
4. Create a pull request with:
   - Clear title describing the change
   - Description of what and why
   - Screenshots/GIFs for UI changes
   - Test steps for reviewers

### PR Template

```markdown
## Summary
Brief description of changes

## Type of Change
- [ ] Bug fix
- [ ] New feature
- [ ] Documentation update
- [ ] Code refactoring

## Testing Done
- [ ] Tested on Windows
- [ ] Tested on Linux
- [ ] Tested on macOS
- [ ] All difficulty levels work
- [ ] No regressions observed

## Screenshots
(if applicable)
```

## Reporting Issues

### Bug Reports

Include:
- OS and version
- Steps to reproduce
- Expected vs actual behavior
- Screenshots if helpful
- Error messages if any

### Feature Requests

Include:
- Clear description of the feature
- Use case / motivation
- Possible implementation approach (optional)

## Areas for Contribution

### Good First Issues
- Improving documentation
- Adding code comments
- UI polish and improvements
- Bug fixes

### Larger Projects
- Localization support
- Custom difficulty settings
- Statistics tracking
- Touch/mobile support

## Code of Conduct

- Be respectful and inclusive
- Provide constructive feedback
- Focus on the code, not the person
- Help others learn and grow

## Questions?

Feel free to open an issue for:
- Questions about the codebase
- Clarification on guidelines
- Discussion of potential features

Thank you for contributing!
