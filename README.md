# Tetris Game in C++

## Introduction
This is a simple *Tetris game* implemented in *C++, using **console graphics* and basic *game loop mechanics. It features **seven different Tetrimino shapes*, real-time movement controls, instant drop functionality, line clearing, and a scoring system.

## Features
- *Real-time movement* (left, right, down, rotate, instant drop)
- *Collision detection* to prevent pieces from overlapping or getting stuck
- *Automatic downward movement* with adjustable speed
- *Line clearing system* (removes full lines and increases score)
- *Score tracking* (each cleared line adds 10 points)
- *Game Over detection* (when the pieces reach the top)

## Controls
- A - Move Left (moves faster when held)
- D - Move Right (moves faster when held)
- S - Move Down
- W - Rotate Piece
- SPACE - Instant Drop
- R - Restart the Game (after Game Over)

## How to Run
1. *Compile the code:*
   sh
   g++ tetris.cpp -o tetris.exe
   
2. *Run the executable:*
   sh
   ./tetris.exe
   

## Dependencies
- Requires *Windows OS* (uses conio.h and windows.h for console manipulation)
- C++11 or later

## Future Improvements
- Adding a *preview* of the next Tetrimino
- Implementing a *hold piece* feature
- Sound effects and improved UI
- Enhancing *AI-based* auto-drop calculations

## Author
- *Developed by:* [Your Name]

Enjoy playing *Tetris*! 🎮
