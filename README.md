# Halma AI

## Description
Halma AI is a C++ implementation of an AI for the board game Halma, utilizing the Min-Max algorithm to choose optimal moves. The AI analyzes possible moves and selects the best strategy to win the game.

## Min-Max Algorithm
The AI uses the **Min-Max** algorithm to evaluate all possible moves and choose the optimal one by minimizing the maximum loss or maximizing the gain. This allows the AI to predict the opponent's moves and plan its strategy accordingly.

## Building
Building requires [CMake](https://cmake.org)
1. Create a build directory:
   ```bash
   mkdir build
   cd build
   ```

2. Run CMake to configure the project:
   ```bash
   cmake ..
   ```

3. Build the project:
   ```bash
   cmake --build .
   ```
Executable main will be created in the build folder
