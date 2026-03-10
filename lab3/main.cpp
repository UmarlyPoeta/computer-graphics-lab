// Lab 3 — Trójkąt z shaderami
// Cel: wyrenderowanie trójkąta przy użyciu Vertex i Fragment shaderów,
//      obiektów VAO i VBO.

#include <iostream>
#include <cmath>
#include <glad/gl.h>
#include <GLFW/glfw3.h>

// ── Źródła shaderów (GLSL) ────────────────────────────────────────────────────
// Vertex shader: transformuje pozycję wierzchołka
const char* vertexShaderSource =
    "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "void main()\n"
    "{\n"
    "    gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
    "}\0";

// Fragment shader: nadaje kolor pikselom
const char* fragmentShaderSource =
    "#version 330 core\n"
    "out vec4 FragColor;\n"
    "void main()\n"
    "{\n"
    "    FragColor = vec4(0.8f, 0.3f, 0.02f, 1.0f);\n"   // pomarańczowy
    "}\n\0";

int main()
{
    // ── 1. Inicjalizacja GLFW i okna ──────────────────────────────────────
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(800, 800, "Trojkat OpenGL", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    gladLoadGL();
    glViewport(0, 0, 800, 800);

    // ── 2. Kompilacja shaderów ─────────────────────────────────────────────
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);

    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);

    // ── 3. Linkowanie programu shaderów ───────────────────────────────────
    GLuint shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    // Shadery skompilowane — obiekty już niepotrzebne
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    // ── 4. Dane geometryczne — wierzchołki trójkąta ───────────────────────
    // Współrzędne w NDC (Normalized Device Coordinates) ∈ <-1, 1>
    GLfloat vertices[] =
    {
        -0.5f, -0.5f * float(sqrt(3.0)) / 3.0f,  0.0f,  // lewy dolny
         0.5f, -0.5f * float(sqrt(3.0)) / 3.0f,  0.0f,  // prawy dolny
         0.0f,  0.5f * float(sqrt(3.0)) * 2.0f / 3.0f, 0.0f  // górny środek
    };

    // ── 5. VAO i VBO ──────────────────────────────────────────────────────
    GLuint VAO, VBO;
    glGenVertexArrays(1, &VAO);  // VAO: zapamiętuje układ atrybutów wierzchołków
    glGenBuffers(1, &VBO);       // VBO: bufor danych na karcie graficznej

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // Powiedz OpenGL jak interpretować dane: atrybut 0, 3 floaty, bez normalizacji
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // Odepnij bufory (dobra praktyka)
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    // ── 6. Główna pętla renderowania ──────────────────────────────────────
    while (!glfwWindowShouldClose(window))
    {
        glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(shaderProgram);   // aktywuj shadery
        glBindVertexArray(VAO);        // aktywuj układ wierzchołków
        glDrawArrays(GL_TRIANGLES, 0, 3);  // narysuj 3 wierzchołki = 1 trójkąt

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // ── 7. Sprzątanie ─────────────────────────────────────────────────────
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteProgram(shaderProgram);
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}
