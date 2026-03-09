# 🪟 Konfiguracja projektu — Windows + Visual Studio

## Krok 1 — Zainstaluj wymagane narzędzia

| Narzędzie | Link | Uwagi |
|-----------|------|-------|
| Visual Studio 2022 | https://visualstudio.microsoft.com/vs/ | Zaznacz: "Desktop development with C++" |
| CMake | https://cmake.org/download/ | Dodaj do PATH podczas instalacji |

## Krok 2 — Pobierz GLFW

1. Idź na https://www.glfw.org/download.html
2. Pobierz **64-bit Windows binaries** (np. `glfw-3.4.bin.WIN64.zip`)
3. Rozpakuj i skopiuj do projektu:
   - `include/GLFW/` → `deps/GLFW/include/GLFW/`
   - `lib-vc2022/glfw3.lib` → `deps/GLFW/lib/glfw3.lib`  
     *(wybierz katalog pasujący do Twojej wersji VS)*

## Krok 3 — Pobierz GLAD

1. Idź na https://glad.dav1d.de/
2. Ustaw parametry:
   - **Language:** C/C++
   - **Specification:** OpenGL
   - **API gl:** Version **3.3**
   - **Profile:** **Core**
   - Zaznacz: **Generate a loader**
3. Kliknij **GENERATE** i pobierz ZIP
4. Skopiuj do projektu:
   - `include/` → `deps/GLAD/include/`
   - `src/glad.c` → `deps/GLAD/src/glad.c`

## Krok 4 — Zbuduj projekt z CMake

```bat
mkdir build
cd build
cmake .. -G "Visual Studio 17 2022" -A x64
cmake --build . --config Release
```

Lub otwórz CMake GUI:
1. **Where is the source code:** ścieżka do folderu projektu
2. **Where to build:** `<projekt>/build`
3. Kliknij **Configure** → wybierz **Visual Studio 17 2022, x64**
4. Kliknij **Generate**
5. Otwórz `.sln` w Visual Studio i builduj

## Krok 5 — Weryfikacja

Uruchom `lab1`. Jeśli program zamknie się bez błędów (exit code 0) — wszystko działa poprawnie.

## Typowe błędy

| Błąd | Rozwiązanie |
|------|-------------|
| `cannot open glfw3.lib` | Sprawdź czy ścieżka `deps/GLFW/lib/glfw3.lib` istnieje |
| `glad.h: No such file` | Sprawdź czy `deps/GLAD/include/glad/glad.h` istnieje |
| `LNK2019: unresolved external` | Upewnij się że CMake linkuje `gdi32`, `user32`, `shell32` |
| Okno natychmiast się zamyka | To normalne w lab1 — `main` zwraca 0 od razu |
