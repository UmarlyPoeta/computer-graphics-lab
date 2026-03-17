
#include <iostream>
#include <cmath>
#include <glad/gl.h>
#include <GLFW/glfw3.h>

const char* vertexShaderSource =
    "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "void main()\n"
    "{\n"
    "    gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
    "}\0";


const char* fragmentShaderSource =
    "#version 330 core\n"
    "out vec4 FragColor;\n"
    "void main()\n"
    "{\n"
    "    FragColor = vec4(0.8f, 0.3f, 0.02f, 1.0f);\n"   // pomarańczowy
    "}\n\0";

int main()
{
    int i = 10, j = 10;
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
    gladLoadGL(glfwGetProcAddress);
    glViewport(0, 0, 800, 800);

    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);

    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);

    GLuint shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    /*
    -1 + d * (2/d), 1 - (r + 1) * (2 / r), 0.0
    -1 + d * (2/d) + 0.3, 1 - (r + 1) * (2/r), 0.0
    -1 + d * (2/d) + 0.3, 1 - r * (2/r), 0.0 

    */
GLfloat vertices[i * j * 9];

    float w = 2.0f / i;
    float h = 2.0f / j;

    int k = 0;

    for (int r = 0; r < j; r++) {
        for (int d = r % 2 == 0 ? 0: 1; d < i; d+= 2) {

            float x = -1.0f + d * w;
            float y =  1.0f - (r + 1) * h;

            // A
            vertices[k++] = x;
            vertices[k++] = y;
            vertices[k++] = 0.0f;

            // B
            vertices[k++] = x + w;
            vertices[k++] = y;
            vertices[k++] = 0.0f;

            // C
            vertices[k++] = x + w;
            vertices[k++] = y + h;
            vertices[k++] = 0.0f;
        }
    }

    GLuint indices[i * j * 3];

    for (int t = 0; t < i * j * 3; t++) {
        indices[t] = t;
    }

    GLuint VAO, VBO, EBO;
    glGenVertexArrays(1, &VAO);  // VAO: zapamiętuje układ atrybutów wierzchołków
    glGenBuffers(1, &VBO);       // VBO: bufor danych na karcie graficznej
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // Odepnij bufory (dobra praktyka)
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    // ── 6. Główna pętla renderowania ──────────────────────────────────────
    while (!glfwWindowShouldClose(window))
    {
        glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(shaderProgram);   // aktywuj shadery
        glBindVertexArray(VAO);        // aktywuj układ wierzchołków
        
        glDrawElements(GL_TRIANGLES, i * j * 3, GL_UNSIGNED_INT, 0);

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
