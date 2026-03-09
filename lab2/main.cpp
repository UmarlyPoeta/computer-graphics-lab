// Lab 2 — Podstawowe okno OpenGL
// Cel: utworzenie okna 800x800 z ciemnym tłem i główną pętlą renderowania.

#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

int main()
{
    // ── 1. Inicjalizacja GLFW ──────────────────────────────────────────────
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // ── 2. Tworzenie okna ─────────────────────────────────────────────────
    // Argumenty: szerokość, wysokość, tytuł, monitor (NULL=okno), kontekst
    GLFWwindow* window = glfwCreateWindow(800, 800, "Opengl-window", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    // ── 3. Ładowanie GLAD (wskaźniki do funkcji OpenGL) ───────────────────
    gladLoadGL();

    // ── 4. Viewport — obszar rysowania w oknie ────────────────────────────
    // glViewport(x_start, y_start, szerokość, wysokość)
    glViewport(0, 0, 800, 800);

    // ── 5. Pierwsze wyczyszczenie ekranu (przed pętlą) ────────────────────
    glClearColor(0.07f, 0.13f, 0.17f, 1.0f); // kolor tła RGBA ∈ <0,1>
    glClear(GL_COLOR_BUFFER_BIT);             // wypełnij back buffer
    glfwSwapBuffers(window);                  // zamień back ↔ front buffer

    // ── 6. Główna pętla renderowania ──────────────────────────────────────
    while (!glfwWindowShouldClose(window))
    {
        // Obsłuż zdarzenia systemowe (zamknięcie, klawiatura, mysz)
        glfwPollEvents();
    }

    // ── 7. Sprzątanie ─────────────────────────────────────────────────────
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}
