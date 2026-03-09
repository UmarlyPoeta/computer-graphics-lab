# 🖥️ Computer Graphics Labs — OpenGL + GLFW

Solutions and exercises for computer graphics labs using **OpenGL 3.3 Core Profile** and the **GLFW** library.

---

## 📁 Project Structure

```
computer-graphics-lab/
├── CMakeLists.txt          # root CMake file (builds all labs)
├── README.md
├── scripts/
│   ├── setup_windows.md    # step-by-step setup guide (Windows / Visual Studio)
│   └── setup_linux.sh      # automatic dependency installer (Linux)
├── deps/
│   └── README.md           # where to place GLFW and GLAD
├── lab1/
│   ├── CMakeLists.txt
│   ├── main.cpp            # ✅ complete solution
│   └── exercise/
│       └── main_exercise.cpp  # 📝 code to fill in
├── lab2/
│   ├── CMakeLists.txt
│   ├── main.cpp
│   └── exercise/
│       └── main_exercise.cpp
└── lab3/
    ├── CMakeLists.txt
    ├── main.cpp
    └── exercise/
        └── main_exercise.cpp
```

---

## 🔧 Requirements

| Tool | Link |
|------|------|
| Visual Studio (Windows) | https://visualstudio.microsoft.com/vs/ |
| CMake ≥ 3.15 | https://cmake.org/download/ |
| GLFW 3.x | https://www.glfw.org/ |
| GLAD (OpenGL 3.3 Core) | https://glad.dav1d.de/ |

---

## 📦 Setting Up Dependencies

### Windows (Visual Studio)

See the step-by-step guide: [`scripts/setup_windows.md`](scripts/setup_windows.md)

### Linux (Ubuntu/Debian)

```bash
chmod +x scripts/setup_linux.sh
./scripts/setup_linux.sh
```

---

## 🏗️ Building the Project

### Windows (CMake + Visual Studio)

```bash
mkdir build
cd build
cmake .. -G "Visual Studio 17 2022" -A x64
cmake --build . --config Release
```

### Linux / macOS

```bash
mkdir build && cd build
cmake ..
make -j$(nproc)
```

Executables will be placed in `build/lab1/`, `build/lab2/`, `build/lab3/`.

---

## 📚 Lab Overview

### Lab 1 — Project Setup
- Installing and linking GLFW + GLAD
- Environment verification (program compiles without errors)

### Lab 2 — Basic OpenGL Window
- Initializing GLFW and OpenGL 3.3 Core context
- Creating a window, setting up viewport, double buffering
- Main render loop

### Lab 3 — First Triangle (Shaders)
- Writing Vertex and Fragment shaders in GLSL
- VAO (Vertex Array Object) and VBO (Vertex Buffer Object)
- Drawing primitives with `glDrawArrays`

---

## 📝 Exercises

Each lab has an `exercise/` folder with a `main_exercise.cpp` file containing **code to complete**. Spots to fill in are marked:

```cpp
// TODO: [task description]
```

Complete solutions are in `main.cpp` in the parent lab directory.

---

## 💡 Tips

- **Core Profile** — modern OpenGL only (recommended)
- **Compatibility Profile** — legacy + modern functions (useful for debugging old code)
- Vertex coordinates in OpenGL use NDC (Normalized Device Coordinates) in the range `<-1.0, 1.0>`
- `glClear` + `glfwSwapBuffers` must be called every frame
