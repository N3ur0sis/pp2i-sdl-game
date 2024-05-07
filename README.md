# Simple Game in C

About the project:

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
- Assimp


**WARNING** 
Update your Version of Opengl to 4.6
On Ubuntu: 

```sh
sudo add-apt-repository ppa:kisak/kisak-mesa -y
sudo apt update && sudo apt upgrade
```
## Build instructions

Only for Debian based/Ubuntu user

**It will ask for sudo password if you have some dependencies to install (don't worry it doesn't install some fancy shit)**

```bash
# Clone this repo
git clone https://github.com/N3ur0sis/pp2i-sdl-game
cd pp2i-sdl-game

#Run scripts, check and install missing deps, build with cmake and run the game
./scripts/run.sh
```

If you're on MacOS: get on Linux.
## TODO List

- [X] not abandon the project
- [ ] remove some memory leaks (just kidding, i'll never do that)
- [x] Basic player movement
- [x] Map creation (Blender) + Level design (in-engine)
- [ ] Dungeons procedural Generation
- [x] Lights
- [x] Basic Shadow Mapping
- [x] Import + Render animation
- [x] Basic Combat system
- [ ] Menu (Main & Pause )
- [ ] GUI
- [ ] Inventory system
- [ ] Trading System
- [ ] Scene Manager
- [ ] Entity Component System
- [ ] Finish the game
- [ ] Find a name for the game


This project is mainly done for fun and partly done because we have to do it if we want to pass the year.




