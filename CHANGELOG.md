# Changelog

All notable changes to this project will be documented in this file.

The format is based on [Keep a Changelog](https://keepachangelog.com/en/1.0.0/),
and this project adheres to [Semantic Versioning](https://semver.org/spec/v2.0.0.html).

## [0.0.1] - 2023-04-23

### Added

- Implemented helper utilities for creating customizable and user-friendly selectable menu options.
- Introduced new `welcome` and `about` screens, providing users with an enhanced initial user experience.
- Added a `.clang-format` configuration file to establish and maintain a consistent and professional code formatting style.
- Expanded inline documentation with more comprehensive comments to improve code understanding and maintainability.
- Added a gif demo showcasing the project's features and functionality for better user understanding.

### Changed

- Refined the minimum screen size requirements to ensure optimal user experience and compatibility across different terminal dimensions.
- Redesigned the game over menu to use a selectable option menu, replacing the previous specific key press functionality for a more intuitive user experience.
- Enhanced the selectable menu with a memory feature that retains the last user selection, streamlining user interactions.
- Improved the selectable menu's flexibility by implementing an adjustable offset value for vertical menu positioning.

### Removed

- None.

## [pre-release] - 2023-04-21

### Added

- Implemented a game speed increase as the snake grows to increase difficulty.
- Added a check for terminal dimensions to ensure the game window fits.
- Introduced dynamic snake size growth without a fixed capacity.
- Added support for arrow keys and additional keys (h, j, k, and l) for snake movement.
- Implemented random initial direction for the snake.
- Improved food generation logic to prevent food from spawning on the snake.
- Added a quit option ('q' key) allowing users to quit the game after game over.
- Introduced a restart option ('r' key) allowing users to restart the game without quitting after game over.
- Enhanced code readability with added comments.
- Added GitHub Actions CI workflow for build checks, linting, and code formatting.

### Changed

- Separated `game` and `screen` code for improved gameplay and general screen control.
- Divided `game` code into `input`, `render`, and `update` modules for better maintainability.

### Removed

- None.

## [pre-release] - 2023-04-19

### Added

- Introduced project introduction and details in `README.md`.
- Added `CHANGELOG.md` file to document project changes.
- Included a `CONTRIBUTING.md` file to provide guidelines for potential contributors.
- Released the project under the GPLv3 license.
- Created `.gitignore` file for excluding unnecessary files and directories from version control.
- Configured `clang-tidy` and `clang-format` for code style enforcement and formatting.
- Set up `Makefile` to build the program.
- Initial implementation of the snake game.

### Changed

- None.

### Removed

- None.
