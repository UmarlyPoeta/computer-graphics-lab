// Lab 1 — Ćwiczenie: weryfikacja środowiska
// ============================================================
// Twoje zadanie: uzupełnij poniższy kod tak, by program:
//   1. Wypisał na ekran wersję biblioteki GLFW
//   2. Skompilował się bez błędów
//
// Przydatna funkcja: glfwGetVersionString()
// Dokumentacja: https://www.glfw.org/docs/latest/intro.html
// ============================================================

#include <iostream>
#include <glad/gl.h>
#include <GLFW/glfw3.h>

int main()
{
    // TODO: zainicjalizuj GLFW (glfwInit)
    if (!glfwInit()) {
        std::cerr << "glfw nie zainijalizowane";
    }
    // TODO: wypisz wersję GLFW na ekran przy użyciu glfwGetVersionString()
    std::cout << glfwGetVersionString() << std::endl;
    // TODO: zakończ GLFW (glfwTerminate)


    glfwTerminate();
    return 0;
}

// ─── Oczekiwany output ─────────────────────────────────────
// Wersja GLFW: 3.x.x ...
// ───────────────────────────────────────────────────────────
