# Tetris for LandTiger

### Embedded systems · C · LandTiger LPC1768

An implementation of Tetris in C for the LandTiger LPC1768 development board.

## Project overview

The objective was to move a classic game from a conventional programming exercise to a real, interactive hardware system. I designed the game to run directly on the board, combining its rules and state management with physical controls, an LCD interface and time-based behaviour.

Working on this project meant approaching programming from a new perspective: not only writing the game logic, but also connecting it to the board's peripherals and responding to hardware input in real time.

🎬 **[Watch the code and gameplay demo](tetris-code-and-gameplay-demo.mp4)**

## Features

- Random tetrominoes, movement, rotation, collision detection, line clearing, scoring and game-over handling.
- Joystick and board-button input for play, pause and piece movement.
- LCD-based game interface.
- **Potentiometer-controlled game speed**, using the board's ADC input to set one of five speed levels.
- Power-ups and random malus events introduced as the player clears lines.

## Final submission

The final version brings together the complete game logic and the board integration. It adds variable speed through the potentiometer, as well as power-ups and random malus events that make the gameplay more dynamic.

## Explore the code

- [Final source code](final-submission/Source)
- [Keil uVision project file](final-submission/sample.uvprojx)
