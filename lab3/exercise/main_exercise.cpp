// Lab 3 — Ćwiczenie: trójkąt z shaderami
// ============================================================
// Uzupełnij kod w miejscach oznaczonych TODO.
// Program powinien wyświetlić RÓWNOBOCZNY TRÓJKĄT w kolorze
// według Twojego wyboru.
//
// TEORIA (przypomnij sobie przed kodowaniem):
//   • Vertex Shader  — przetwarza każdy wierzchołek osobno
//   • Fragment Shader — przetwarza każdy piksel (fragment)
//   • VBO — bufor z danymi wierzchołków (na GPU)
//   • VAO — opis formatu tych danych (co oznacza każdy float)
//   • NDC — układ współrzędnych OpenGL: środek=(0,0), rogi=±1
// ============================================================

#include <iostream>
#include <cmath>
#include <glad/gl.h>
#include <GLFW/glfw3.h>

// TODO [1/7]: Wpisz kod GLSL dla Vertex Shadera.
// Shader powinien przyjąć atrybut vec3 aPos (location=0)
// i ustawić gl_Position.
const char* vertexShaderSource =
    /* TODO */
    nullptr;

// TODO [2/7]: Wpisz kod GLSL dla Fragment Shadera.
// Shader powinien zwrócić kolor — wybierz swój ulubiony (RGBA ∈ <0,1>).
const char* fragmentShaderSource =
    /* TODO */
    nullptr;

int main()
{
    // TODO [3/7]: Inicjalizacja GLFW, okno 800x800, GLAD, viewport
    // (skopiuj z Lab 2 i dostosuj tytuł)

    // TODO [4/7]: Skompiluj oba shadery i zlinkuj program shaderów.
    // Schemat dla każdego shadera:
    //   GLuint shader = glCreateShader(TYP);
    //   glShaderSource(shader, 1, &zrodlo, NULL);
    //   glCompileShader(shader);
    // Potem: utwórz program, attach, link, usuń shadery.

    GLuint shaderProgram = 0; // zastąp poprawnym programem

    // ── Wierzchołki trójkąta ─────────────────────────────────────────────
    // Równoboczny trójkąt wyśrodkowany w (0,0):
    //   lewy dolny: (-0.5,  -√3/6,  0)
    //   prawy dolny:( 0.5,  -√3/6,  0)
    //   górny:      ( 0.0,   √3/3,  0)
    //
    // TODO [5/7]: Uzupełnij tablicę wierzchołków (9 floatów, 3 wierzchołki × xyz)
    GLfloat vertices[] =
    {
        /* TODO */
    };

    // TODO [6/7]: Stwórz VAO i VBO, załaduj dane, skonfiguruj atrybuty.
    // Kolejność:
    //   glGenVertexArrays → glGenBuffers
    //   glBindVertexArray → glBindBuffer(ARRAY_BUFFER)
    //   glBufferData → glVertexAttribPointer → glEnableVertexAttribArray
    //   Odepnij oba (bind 0)
    GLuint VAO = 0, VBO = 0; // zastąp poprawną inicjalizacją

    // TODO [7/7]: Pętla renderowania.
    // W każdej klatce: ClearColor → Clear → UseProgram → BindVAO
    //                  → DrawArrays(GL_TRIANGLES, 0, 3) → SwapBuffers → PollEvents

    // Sprzątanie
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteProgram(shaderProgram);
    glfwDestroyWindow(/* window */nullptr);
    glfwTerminate();
    return 0;
}

// ─── Oczekiwany efekt ──────────────────────────────────────
// Okno z ciemnym tłem i kolorowym trójkątem pośrodku.
// ───────────────────────────────────────────────────────────
//
// DODATKOWE WYZWANIA (+):
//
// [A] Zmień kolor trójkąta na niebieski (0.2, 0.4, 0.9, 1.0)
//
// [B] Narysuj dwa trójkąty obok siebie.
//     Wskazówka: dodaj 3 wierzchołki do tablicy i zmień
//     ostatni argument glDrawArrays z 3 na 6.
//
// [C] Dodaj obsługę błędów kompilacji shadera:
//     GLint success;
//     glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
//     if (!success) { /* glGetShaderInfoLog i wypisz błąd */ }
