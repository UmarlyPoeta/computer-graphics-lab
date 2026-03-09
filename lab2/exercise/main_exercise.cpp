// Lab 2 — Ćwiczenie: podstawowe okno OpenGL
// ============================================================
// Uzupełnij poniższy kod w miejscach oznaczonych TODO.
// Program powinien:
//   1. Otworzyć okno 800x800 z tytułem "Moje okno OpenGL"
//   2. Ustawić kolor tła na granatowy: (0.1, 0.1, 0.4, 1.0)
//   3. Reagować na zamknięcie okna (X lub Alt+F4)
//
// PODPOWIEDZI:
//   - glfwWindowHint ustawiasz PRZED glfwCreateWindow
//   - gladLoadGL() musi być PO glfwMakeContextCurrent
//   - glViewport definiuje prostokąt rysowania wewnątrz okna
// ============================================================

#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

int main()
{
    // TODO [1/6]: zainicjalizuj GLFW
    // glfwInit();

    // TODO [2/6]: ustaw wersję OpenGL 3.3 Core Profile
    // (3 wywołania glfwWindowHint)

    // TODO [3/6]: utwórz okno 800x800 o tytule "Moje okno OpenGL"
    // GLFWwindow* window = ...
    // Sprawdź czy window != NULL i obsłuż błąd

    // TODO [4/6]: ustaw kontekst okna jako aktywny i załaduj GLAD

    // TODO [5/6]: ustaw viewport (cały obszar okna 800x800)

    // Pierwsze czyszczenie ekranu — granatowe tło
    // TODO: ustaw kolor (0.1f, 0.1f, 0.4f, 1.0f) i wyczyść bufor
    // TODO: wywołaj glfwSwapBuffers

    // TODO [6/6]: napisz główną pętlę while(!glfwWindowShouldClose)
    // Wewnątrz: glfwPollEvents()

    // TODO: zwolnij zasoby (glfwDestroyWindow, glfwTerminate)

    return 0;
}

// ─── Oczekiwany efekt ──────────────────────────────────────
// Okno 800x800 z granatowym tłem, zamykane przez X.
// ───────────────────────────────────────────────────────────
//
// DODATKOWE WYZWANIE (+):
//   Spraw, by okno reagowało na klawisz ESC i zamykało się.
//   Przydatna funkcja: glfwGetKey(window, GLFW_KEY_ESCAPE)
//   Wskazówka: wewnątrz pętli sprawdź klawisz i wywołaj
//              glfwSetWindowShouldClose(window, true)
