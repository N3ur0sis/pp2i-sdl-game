# PP2I Game in C

Recap of the project : (after brainstorming (w/ arthur))

The game is meant to be a 3D isometric game with simple yet clean graphics (inspired by tunic)
Consists of exploring a map, entering dungeons, beating enemy winning junk, buying/trading the junk we've earned
to get better stuff to beat stronger enemy to earn better junk.


## Dependencies

- Git
- C compiler (gcc)
- CMake  (to write makefile faster)
- SDL2
- GLAD (OpenGL API)

First check you have all the dependencies

```sh
sudo apt install git build-essential pkg-config cmake cmake-data libsdl2-dev libsdl2-gfx-dev
```

## Build instructions

Only for Debian based/Ubuntu user (for macOS, i guess it's similar)


## Build instructions

```sh
# Clone this repo
git clone https://github.com/N3ur0sis/pp2i-sdl-game
cd pp2i-sdl-game

# Go to build folder
cd build

# Build
cmake ..
make

# Run
./pp2i
```
![Repository Map](https://github.com/N3ur0sis/pp2i-sdl-game/blob/main/image.png)

This project is maintained by Aymeric, Arthur, Baptiste and Victor 




