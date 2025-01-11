# Cirobb Engine WASM

Cirobb is a 2D physics engine written in C++ and compiled to WebAssembly, designed to simulate rigid bodies with collision detection and resolution.

## Features

- 2D Physics Engine supporting:

  - Dynamic and static rigid bodies
  - Geometric shapes: Circles and OBB (Oriented Bounding Box)
  - Discrete Collision Detection (DCD)
  - Impulse-based collision resolution
  - Friction and restitution
  - Configurable gravity
  - Position correction (Baumgarte and NGS)

- WebAssembly compilation for web browser usage
- OpenGL/WebGL rendering
- Interactive controls for object creation and manipulation

## Demo

The project includes a web demonstration where you can:

- Press 'B' to create boxes
- Press 'C' to create circles
- Press 'P' to pause/resume simulation
- Press 'SPACE' to change position correction type

## Installation

### Requirements

- Emscripten SDK
- CMake
- C++11 compatible compiler
- Python 3.10

### Building

To compile the project to WebAssembly:

```bash
./build.sh
```
