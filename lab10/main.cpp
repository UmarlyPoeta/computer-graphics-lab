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
static int gWidth = WIDTH;
static int gHeight = HEIGHT;
static unsigned int gFBO = 0;
static unsigned int gFramebufferTexture = 0;
static unsigned int gRBO = 0;

GLfloat vertices[] =
{ // COORDINATES      / COLORS           / TexCoord //
  -0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,  0.0f, 0.0f,
  -0.5f,  0.5f, 0.0f,  0.0f, 1.0f, 0.0f,  0.0f, 1.0f,
   0.5f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f,  1.0f, 1.0f,
   0.5f, -0.5f, 0.0f,  1.0f, 1.0f, 1.0f,  1.0f, 0.0f
};

GLuint indices[] = {
    0, 1, 2,
    2, 3, 0
};

GLfloat quadVertices[] =
{ // COORDINATES / TexCoord
    -1.0f,  1.0f,  0.0f, 1.0f,
    -1.0f, -1.0f,  0.0f, 0.0f,
     1.0f, -1.0f,  1.0f, 0.0f,
    -1.0f,  1.0f,  0.0f, 1.0f,
     1.0f, -1.0f,  1.0f, 0.0f,
     1.0f,  1.0f,  1.0f, 1.0f
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
        "lab10/textures/" + fileName,
        "build/lab10/textures/" + fileName,
        "../textures/" + fileName,
        "../build/lab10/textures/" + fileName
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

static void setKernel(GLuint program, const float* kernel)
{
    glUniform1fv(glGetUniformLocation(program, "kernel"), 9, kernel);
}

static void resizeFramebuffer(int width, int height)
{
    if (width <= 0 || height <= 0)
        return;

    glBindTexture(GL_TEXTURE_2D, gFramebufferTexture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);

    glBindRenderbuffer(GL_RENDERBUFFER, gRBO);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, width, height);

    glBindTexture(GL_TEXTURE_2D, 0);
    glBindRenderbuffer(GL_RENDERBUFFER, 0);
}

static void framebufferSizeCallback(GLFWwindow* window, int width, int height)
{
    if (width <= 0 || height <= 0)
        return;

    gWidth = width;
    gHeight = height;
    glViewport(0, 0, width, height);

    if (gFBO != 0 && gFramebufferTexture != 0 && gRBO != 0)
    {
        resizeFramebuffer(width, height);
        glBindFramebuffer(GL_FRAMEBUFFER, gFBO);
        if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
            std::cerr << "Framebuffer is not complete after resize." << std::endl;
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
    }
}

int main()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "Lab10 - Framebuffer", NULL, NULL);
    if (!window) { glfwTerminate(); return -1; }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);

    gladLoadGL(glfwGetProcAddress);
    glViewport(0, 0, WIDTH, HEIGHT);

    Shader sceneShader("shaders/default.vert", "shaders/default.frag");
    Shader framebufferShader("shaders/framebuffer.vert", "shaders/framebuffer.frag");

    VAO quadVAO;
    quadVAO.Bind();
    VBO quadVBO(vertices, sizeof(vertices));
    EBO quadEBO(indices, sizeof(indices));
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);
    quadVAO.Unbind();
    quadVBO.Unbind();
    quadEBO.Unbind();

    VAO screenVAO;
    screenVAO.Bind();
    VBO screenVBO(quadVertices, sizeof(quadVertices));
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));
    glEnableVertexAttribArray(1);
    screenVAO.Unbind();
    screenVBO.Unbind();

    const std::string texPath = resolveTexturePath("pop_cat.png");
    Texture popCat(texPath.c_str(), GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
    popCat.texUnit(sceneShader, "tex0", 0);

    glGenFramebuffers(1, &gFBO);
    glBindFramebuffer(GL_FRAMEBUFFER, gFBO);

    glGenTextures(1, &gFramebufferTexture);
    glBindTexture(GL_TEXTURE_2D, gFramebufferTexture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, gWidth, gHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, gFramebufferTexture, 0);

    glGenRenderbuffers(1, &gRBO);
    glBindRenderbuffer(GL_RENDERBUFFER, gRBO);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, gWidth, gHeight);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, gRBO);

    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
    {
        std::cerr << "Framebuffer is not complete." << std::endl;
    }

    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    framebufferShader.Activate();
    glUniform1i(glGetUniformLocation(framebufferShader.ID, "screenTexture"), 0);

    GLuint scaleUni = glGetUniformLocation(sceneShader.ID, "scale");
    GLuint texelSizeLoc = glGetUniformLocation(framebufferShader.ID, "texelSize");
    GLuint filterModeLoc = glGetUniformLocation(framebufferShader.ID, "filterMode");

    const float kernelIdentity[9] = {
        0.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 0.0f
    };
    const float kernelBlur[9] = {
        1.0f / 9.0f, 1.0f / 9.0f, 1.0f / 9.0f,
        1.0f / 9.0f, 1.0f / 9.0f, 1.0f / 9.0f,
        1.0f / 9.0f, 1.0f / 9.0f, 1.0f / 9.0f
    };
    const float kernelSharpen[9] = {
         0.0f, -1.0f,  0.0f,
        -1.0f,  5.0f, -1.0f,
         0.0f, -1.0f,  0.0f
    };
    const float kernelEdge[9] = {
        1.0f,  1.0f, 1.0f,
        1.0f, -8.0f, 1.0f,
        1.0f,  1.0f, 1.0f
    };

    int filterMode = 0;

    while (!glfwWindowShouldClose(window))
    {
        if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS)
            filterMode = 0;
        if (glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS)
            filterMode = 1;
        if (glfwGetKey(window, GLFW_KEY_3) == GLFW_PRESS)
            filterMode = 2;
        if (glfwGetKey(window, GLFW_KEY_4) == GLFW_PRESS)
            filterMode = 3;

        glBindFramebuffer(GL_FRAMEBUFFER, gFBO);
        glEnable(GL_DEPTH_TEST);
        glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        sceneShader.Activate();
        glUniform1f(scaleUni, 0.5f);
        glActiveTexture(GL_TEXTURE0);
        popCat.Bind();
        quadVAO.Bind();
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        glBindFramebuffer(GL_FRAMEBUFFER, 0);
        glDisable(GL_DEPTH_TEST);
        glClearColor(0.10f, 0.10f, 0.10f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        framebufferShader.Activate();
        glUniform2f(texelSizeLoc, 1.0f / gWidth, 1.0f / gHeight);
        glUniform1i(filterModeLoc, filterMode);
        if (filterMode == 1)
            setKernel(framebufferShader.ID, kernelBlur);
        else if (filterMode == 2)
            setKernel(framebufferShader.ID, kernelSharpen);
        else if (filterMode == 3)
            setKernel(framebufferShader.ID, kernelEdge);
        else
            setKernel(framebufferShader.ID, kernelIdentity);

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, gFramebufferTexture);
        screenVAO.Bind();
        glDrawArrays(GL_TRIANGLES, 0, 6);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    popCat.Delete();
    quadVAO.Delete();
    quadVBO.Delete();
    quadEBO.Delete();
    screenVAO.Delete();
    screenVBO.Delete();
    sceneShader.Delete();
    framebufferShader.Delete();
    glDeleteTextures(1, &gFramebufferTexture);
    glDeleteRenderbuffers(1, &gRBO);
    glDeleteFramebuffers(1, &gFBO);
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}
