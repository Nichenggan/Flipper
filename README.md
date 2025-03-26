# Flipper


![Language](https://img.shields.io/badge/language-C%2B%2B-blue)
![School](https://img.shields.io/badge/school-ESIEE-orange)
![Author](https://img.shields.io/badge/author-Chenyi%20Li-brightgreen)
## Description

Flipper is a simple 2D game where a ball bounces around the screen, interacting with various elements such as bumpers and walls. The game is designed to be a fun and engaging way to practice programming skills in C++.

## Features

- **Ball Movement**: The ball moves around the screen, bouncing off walls and other objects.
- **Bumpers**: The game includes bumpers that the ball can interact with.
- **Pause Functionality**: The game can be paused and resumed using the 'P' key.
- **Window Management**: The game window can be closed using the 'ESC' key.

## Installation

To build and run the game, you need to have CMake, OpenGL, and GLUT installed on your system.

1. Clone the repository:
    ```sh
    git clone https://github.com/yourusername/Flipper.git
    cd Flipper
    ```

2. Create a build directory and navigate into it:
    ```sh
    mkdir build
    cd build
    ```

3. Run CMake to configure the project:
    ```sh
    cmake ..
    ```

4. Build the project:
    ```sh
    make
    ```

5. Run the game:
    ```sh
    ./Flipper
    ```

## Usage

- **P Key**: Pause and resume the game.
- **ESC Key**: Close the game window and exit the game.

## Dependencies

- **C++11**: The game is written in C++11.
- **OpenGL**: Used for rendering graphics.
- **GLUT**: Used for window management and input handling.

## File Structure

- `Eleve.cpp`: Main game logic and rendering functions.
- `G2D.h`, `G2DColor.cpp`, `G2Dfull.h`, `G2DKey.cpp`, `G2DMain.cpp`, `G2DMouse.cpp`, `G2DPPM.cpp`, `G2DX.cpp`: Graphics and utility functions.
- `V2.cpp`, `V2.h`: Vector math utilities.
- `CMakeLists.txt`: Build configuration file.

## License

This project is licensed under the MIT License. See the `LICENSE` file for details.

## Author

- **Chenyi Li** -  [Personal Page](https://github.com/Nichenggan)

## Changelog

### 2025-03-12

- Updated README.
- Initialized game files.
****
### 2025-03-26

- Fini
****
