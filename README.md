# Bomberman

A simple Bomberman-style prototype built in C++ with SDL2 rendering and modular game logic.

## Project structure

- `CMakeLists.txt` — build configuration
- `src/` — C++ source code for game logic, rendering, and level loading
- `levels/` — text-based level files
- `build/` — CMake build output directory

## Build

```bash
cd /workspaces/Bomberman
mkdir -p build
cd build
cmake ..
cmake --build .
```

## Run

From the project root:

```bash
cd /workspaces/Bomberman
SDL_VIDEODRIVER=dummy ./build/Bomberman
```

If your environment supports SDL2 windows, omit `SDL_VIDEODRIVER=dummy`:

```bash
cd /workspaces/Bomberman
./build/Bomberman
```

## Level files

The default level is loaded from `levels/level1.txt`. You can also pass a custom path:

```bash
./build/Bomberman levels/level1.txt
```

## Notes

- The game currently includes basic enemy chase behavior and level loading.
- Rendering is handled with SDL2 if available.
