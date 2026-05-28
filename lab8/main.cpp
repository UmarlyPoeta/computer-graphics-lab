#include <array>
#include <fstream>
#include <iostream>
#include <string>
#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include "shaderClass.h"
#include "VAO.h"
#include "VBO.h"
#include "EBO.h"
#include "Texture.h"

const int WIDTH = 800, HEIGHT = 800;

GLfloat vertices[] =
{ // COORDINATES      / COLORS           / TexCoord //
  -0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,  0.0f, 0.0f, // Lower left corner
  -0.5f,  0.5f, 0.0f,  0.0f, 1.0f, 0.0f,  0.0f, 1.0f, // Upper left corner
   0.5f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f,  1.0f, 1.0f, // Upper right corner
   0.5f, -0.5f, 0.0f,  1.0f, 1.0f, 1.0f,  1.0f, 0.0f  // Lower right corner
};

GLuint indices[] = {
    0, 1, 2,
    2, 3, 0
};

static bool fileExists(const std::string& path)
{
    std::ifstream file(path);
    return file.good();
}

static std::string resolveTexturePath(const std::string& fileName)
{
    const std::array<std::string, 5> candidates = {
        "textures/" + fileName,
        "lab8/textures/" + fileName,
        "build/lab8/textures/" + fileName,
        "../textures/" + fileName,
        "../build/lab8/textures/" + fileName
    };

    for (const auto& path : candidates)
    {
        if (fileExists(path))
        {
            return path;
        }
    }

    return "textures/" + fileName;
}

int main()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "Lab8 - Texturing", NULL, NULL);
    if (!window) { glfwTerminate(); return -1; }
    glfwMakeContextCurrent(window);

    gladLoadGL(glfwGetProcAddress);
    glViewport(0, 0, WIDTH, HEIGHT);

    Shader shaderProgram("shaders/default.vert", "shaders/default.frag");

    VAO VAO1;
    VAO1.Bind();
    VBO VBO1(vertices, sizeof(vertices));
    EBO EBO1(indices, sizeof(indices));

    // Atrybut 0: Pozycje
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // Atrybut 1: Kolory
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    // Atrybut 2: Współrzędne tekstury
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);

    VAO1.Unbind();
    VBO1.Unbind();
    EBO1.Unbind();

    // Ładowanie tekstur
    const std::string texPath = resolveTexturePath("pop_cat.png");
    Texture popCat(texPath.c_str(), GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
    Texture popCat2(texPath.c_str(), GL_TEXTURE_2D, GL_TEXTURE1, GL_RGBA, GL_UNSIGNED_BYTE);
    popCat.texUnit(shaderProgram, "texture1", 0);
    popCat2.texUnit(shaderProgram, "texture2", 1);

    // Przesyłamy zmienną scale z Vertex Shadera
    GLuint scaleUni = glGetUniformLocation(shaderProgram.ID, "scale");

    while (!glfwWindowShouldClose(window))
    {
        glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        shaderProgram.Activate();
        glUniform1f(scaleUni, 0.5f); // Możesz zmieniać skalę tutaj

        glActiveTexture(GL_TEXTURE0);
        popCat.Bind();
        glActiveTexture(GL_TEXTURE1);
        popCat2.Bind();
        VAO1.Bind();
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    popCat.Delete();
    popCat2.Delete();
    VAO1.Delete(); VBO1.Delete(); EBO1.Delete();
    shaderProgram.Delete();
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}
