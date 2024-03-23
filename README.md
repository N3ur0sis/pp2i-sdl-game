# PP2I Game in C

About the porject:

The game is meant to be a 3D isometric game with simple yet clean graphics (inspired by tunic)
Consists of exploring a map, entering dungeons, beating enemy, winning junk, buying/trading the junk we've earned
to get better stuff to beat stronger enemy to earn better junk. 
Gameplay inspired by zelda.


## Dependencies

- Git
- C compiler (gcc)
- CMake  (to write makefile faster)
- SDL2
- GLAD (OpenGL API)
- [CGLM](https://github.com/recp/cglm)

You can install all the deps by running the following command (but the run script will do it automatically, see below)

```sh
sudo apt install git build-essential pkg-config cmake cmake-data libsdl2-dev libsdl2-gfx-dev
```

## Build instructions

Only for Debian based/Ubuntu user (for macOS, i guess it's similar)

```bash
# Clone this repo
git clone https://github.com/N3ur0sis/pp2i-sdl-game
cd pp2i-sdl-game

#Run scripts, check and install missing deps, build with cmake and run the game
./scripts/run.sh
```

## TODO List

- [ ] Basic player movement
- [ ] Map creation (Blender) + Level design (in-engine)
- [ ] Dungeons procedural Generation
- [x] Light system (fixes needed) 
- [ ] Import + Render animation
- [ ] Basic Combat system
- [ ] Menu (Main + Options)
- [ ] GUI
- [ ] Inventory system


![Repository Map](https://github.com/N3ur0sis/pp2i-sdl-game/blob/main/docs/architecture.png)

This project is maintained by Aymeric, Arthur, Baptiste, Victor and Mathis 




