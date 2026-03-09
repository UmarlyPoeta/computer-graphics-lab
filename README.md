# 🖥️ Computer Graphics Labs — OpenGL + GLFW

Repozytorium zawiera rozwiązania laboratoriów z grafiki komputerowej prowadzonych przy użyciu **OpenGL 3.3 Core Profile** i biblioteki **GLFW**.

---

## 📁 Struktura projektu

```
computer-graphics-lab/
├── CMakeLists.txt          # główny plik CMake (buduje wszystkie laby)
├── README.md
├── scripts/
│   ├── setup_windows.md    # instrukcja instalacji bibliotek (Windows / Visual Studio)
│   └── setup_linux.sh      # automatyczna instalacja zależności (Linux)
├── deps/
│   └── README.md           # gdzie umieścić GLFW i GLAD
├── lab1/
│   ├── CMakeLists.txt
│   ├── main.cpp            # ✅ rozwiązanie
│   └── exercise/
│       └── main_exercise.cpp  # 📝 ćwiczenie do uzupełnienia
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

## 🔧 Wymagania

| Narzędzie | Link |
|-----------|------|
| Visual Studio (Windows) | https://visualstudio.microsoft.com/vs/ |
| CMake ≥ 3.15 | https://cmake.org/download/ |
| GLFW 3.x | https://www.glfw.org/ |
| GLAD (OpenGL 3.3 Core) | https://glad.dav1d.de/ |

---

## 📦 Przygotowanie bibliotek

### Windows (Visual Studio)

Szczegółowa instrukcja krok po kroku: [`scripts/setup_windows.md`](scripts/setup_windows.md)

### Linux (Ubuntu/Debian)

```bash
chmod +x scripts/setup_linux.sh
./scripts/setup_linux.sh
```

---

## 🏗️ Budowanie projektu

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

Pliki wykonywalne znajdziesz w `build/lab1/`, `build/lab2/`, `build/lab3/`.

---

## 📚 Opis laboratoriów

### Lab 1 — Konfiguracja projektu
- Instalacja i linkowanie GLFW + GLAD
- Weryfikacja środowiska (program kompiluje się bez błędów)

### Lab 2 — Podstawowe okno OpenGL
- Inicjalizacja GLFW i kontekstu OpenGL 3.3 Core
- Tworzenie okna, viewport, double buffering
- Główna pętla renderowania

### Lab 3 — Pierwszy trójkąt (shadery)
- Vertex Shader i Fragment Shader w GLSL
- VAO (Vertex Array Object) i VBO (Vertex Buffer Object)
- Rysowanie prymitywów: `glDrawArrays`

---

## 📝 Ćwiczenia

Każde laboratorium posiada katalog `exercise/` z plikiem `main_exercise.cpp` zawierającym **kod do uzupełnienia**. Miejsca do wypełnienia są oznaczone:

```cpp
// TODO: [opis zadania]
```

Gotowe rozwiązania znajdziesz w `main.cpp` w katalogu nadrzędnym.

---

## 💡 Wskazówki

- **Core Profile** — tylko nowoczesne funkcje OpenGL (zalecane)
- **Compatibility Profile** — stare + nowe funkcje (do debugowania legacy kodu)
- Współrzędne wierzchołków w OpenGL są w zakresie `<-1.0, 1.0>` (NDC — Normalized Device Coordinates)
- `glClear` + `glfwSwapBuffers` muszą być wywoływane w każdej klatce
