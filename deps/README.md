# Zależności (deps/)

Umieść tutaj pobrane biblioteki w następującej strukturze:

```
deps/
├── GLFW/
│   ├── include/
│   │   └── GLFW/
│   │       ├── glfw3.h
│   │       └── glfw3native.h
│   └── lib/
│       └── glfw3.lib          (Windows) / libglfw3.a (Linux)
└── GLAD/
    ├── include/
    │   ├── glad/
    │   │   └── glad.h
    │   └── KHR/
    │       └── khrplatform.h
    └── src/
        └── glad.c
```

## Skąd pobrać?

### GLFW
1. Idź na https://www.glfw.org/download.html
2. Pobierz **64-bit Windows binaries**
3. Skopiuj `include/` i odpowiedni katalog `lib/` (np. `lib-vc2022/`)

### GLAD
1. Idź na https://glad.dav1d.de/
2. Ustaw:
   - Language: **C/C++**
   - Specification: **OpenGL**
   - API gl: **Version 3.3**
   - Profile: **Core**
3. Kliknij **Generate**
4. Pobierz ZIP i skopiuj `include/` i `src/` do `deps/GLAD/`
