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
#include <glad/gl.h>
#include <GLFW/glfw3.h>

int main()
{
    // TODO [1/6]: zainicjalizuj GLFW
    // glfwInit();
    glfwInit();

    // TODO [2/6]: ustaw wersję OpenGL 3.3 Core Profile
    // (3 wywołania glfwWindowHint)
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE);

    // TODO [3/6]: utwórz okno 800x800 o tytule "Moje okno OpenGL"
    // GLFWwindow* window = ...
    // Sprawdź czy window != NULL i obsłuż błąd
    GLFWwindow * window = glfwCreateWindow(800, 800, "Moje okno OpenGL", NULL, NULL);

    if (window == NULL) {
        std::cout<<"Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }

    // TODO [4/6]: ustaw kontekst okna jako aktywny i załaduj GLAD

    glfwMakeContextCurrent(window);
    gladLoadGL(glfwGetProcAddress);

    // TODO [5/6]: ustaw viewport (cały obszar okna 800x800)
    glViewport(0, 0, 800, 800);
    // Pierwsze czyszczenie ekranu — granatowe tło
    // TODO: ustaw kolor (0.1f, 0.1f, 0.4f, 1.0f) i wyczyść bufor
    // TODO: wywołaj glfwSwapBuffers
    glClearColor(0.1f, 0.1f, 0.4f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    glfwSwapBuffers(window);

    // TODO [6/6]: napisz główną pętlę while(!glfwWindowShouldClose)
    // Wewnątrz: glfwPollEvents()
    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();
    }

    // TODO: zwolnij zasoby (glfwDestroyWindow, glfwTerminate)
    glfwDestroyWindow(window);
    glfwTerminate();

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
