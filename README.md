# spaceballs-game
Asteroid dodger game, running on atmega328p microprocessor.

Completed for GE1111 at Northeastern University.

My partner did the wiring/integration, I wrote the code.

Video (skip to 1:20 for demo): https://www.youtube.com/watch?v=GlxY4KX8KSw

## description

The game is represented in a 16x2 matrix, and printed onto a 16x2 LCD screen.  The player is represented by a carrot (>) on the left side of the screen.  Up and down buttons allow the character to move to avoid asteroids coming from the right side of the screen.  Only one asteroid is present on the screen at a time.  A random number generator determines whether the asteroid is on the top or bottom.  Each asteroid comes at the player slightly faster than the last asteroid.  The game ends when the player gets hit.
