# cub3D

A simple 3D game engine based on **raycasting**, inspired by *Wolfenstein 3D*, developed in **C** as part of the 42 curriculum.  
The project focuses on graphics programming, event handling, and mathematical concepts required to render a pseudo-3D environment from a 2D map.

---

## 📌 Features

- Real-time raycasting engine
- First-person camera view
- Textured walls
- Player movement:
  - Forward / backward
  - Strafe left / right
  - Rotate camera
- Collision detection
- Minimap (optional / bonus)
- Mouse support (bonus)
- Floor and ceiling coloring
- Smooth rendering loop

---

## 🧠 What This Project Demonstrates

- Raycasting algorithms
- Linear algebra and trigonometry
- Pixel-level rendering
- Event-driven programming
- Game loop implementation
- Parsing and validating configuration files
- Memory management and performance optimization in C

---

## 🛠️ Technologies

- Language: **C**
- Graphics library:
  - **MLX42** simplified version of MiniLibX for 42 school
- Platform:
  - Linux / macOS
- Math:
  - vectors, angles, trigonometric functions

---

## 🚀 Build & Run

### Requirements
- `gcc` or `clang`
- `make`
- `MLX42` installed

### Compilation
```bash
make
```

### Run
```bash
./cub3D maps/map.cub
```

---

## 🗺️ Map Format (`.cub`)

Example:
```
NO ./textures/wall_north.xpm
SO ./textures/wall_south.xpm
WE ./textures/wall_west.xpm
EA ./textures/wall_east.xpm

F 220,100,0
C 225,30,0

111111
100001
101101
1000N1
111111
```

- `NO`, `SO`, `WE`, `EA`: wall textures
- `F`, `C`: floor and ceiling colors
- `1`: wall
- `0`: empty space
- `N`, `S`, `E`, `W`: player starting position and orientation

---

## 🧪 Testing

- Tested on multiple maps
- Manual comparison with reference implementation
- Memory checked with:
```bash
valgrind --leak-check=full ./cub3D maps/map.cub
```

---

## ⚠️ Limitations

- Not a full 3D engine
- No vertical movement
- Rendering limited to raycasting constraints
- Designed strictly according to 42 subject requirements

---

## 📂 Project Structure (example)

```
cub3D/
├── src/
├── bonus/
├── libft/
├── include/
├── images/
├── maps/
├── MLX42/
├── Makefile
└── README.md
```

---

## 👤 Author

- **aiturria**
- **angcampo**  
  42 Málaga

---

## 📄 License

This project is for educational purposes as part of the 42 curriculum.
