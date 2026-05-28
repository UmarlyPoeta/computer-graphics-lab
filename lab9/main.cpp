#include <cmath>
#include <iostream>
#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "shaderClass.h"
#include "VAO.h"
#include "VBO.h"
#include "EBO.h"
#include "Texture.h"
#include "Camera.h"

const int WIDTH = 800, HEIGHT = 800;

GLfloat pyramidVertices[] =
{ // COORDINATES           / COLORS           / TexCoord / NORMALS
    -0.5f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f,  0.0f, 0.0f,   0.0f, -1.0f, 0.0f,
    -0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,  0.0f, 5.0f,   0.0f, -1.0f, 0.0f,
     0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,  5.0f, 5.0f,   0.0f, -1.0f, 0.0f,
     0.5f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f,  5.0f, 0.0f,   0.0f, -1.0f, 0.0f,

    -0.5f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f,  0.0f, 0.0f,  -0.8f,  0.5f, 0.0f,
    -0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,  5.0f, 0.0f,  -0.8f,  0.5f, 0.0f,
     0.0f, 0.8f,  0.0f,     0.92f, 0.86f, 0.76f,  2.5f, 5.0f,  -0.8f,  0.5f, 0.0f,

    -0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,  5.0f, 0.0f,   0.0f,  0.5f, -0.8f,
     0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,  0.0f, 0.0f,   0.0f,  0.5f, -0.8f,
     0.0f, 0.8f,  0.0f,     0.92f, 0.86f, 0.76f,  2.5f, 5.0f,   0.0f,  0.5f, -0.8f,

     0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,  0.0f, 0.0f,   0.8f,  0.5f, 0.0f,
     0.5f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f,  5.0f, 0.0f,   0.8f,  0.5f, 0.0f,
     0.0f, 0.8f,  0.0f,     0.92f, 0.86f, 0.76f,  2.5f, 5.0f,   0.8f,  0.5f, 0.0f,

     0.5f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f,  5.0f, 0.0f,   0.0f,  0.5f, 0.8f,
    -0.5f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f,  0.0f, 0.0f,   0.0f,  0.5f, 0.8f,
     0.0f, 0.8f,  0.0f,     0.92f, 0.86f, 0.76f,  2.5f, 5.0f,   0.0f,  0.5f, 0.8f
};

GLuint pyramidIndices[] =
{
    0, 1, 2, 0, 2, 3,
    4, 6, 5,
    7, 9, 8,
    10, 12, 11,
    13, 15, 14
};

GLfloat planeVertices[] =
{ // COORDINATES           / COLORS           / TexCoord / NORMALS
    -2.5f, 0.0f,  2.5f,     0.60f, 0.60f, 0.60f,  0.0f, 0.0f,   0.0f, 1.0f, 0.0f,
    -2.5f, 0.0f, -2.5f,     0.60f, 0.60f, 0.60f,  0.0f, 4.0f,   0.0f, 1.0f, 0.0f,
     2.5f, 0.0f, -2.5f,     0.60f, 0.60f, 0.60f,  4.0f, 4.0f,   0.0f, 1.0f, 0.0f,
     2.5f, 0.0f,  2.5f,     0.60f, 0.60f, 0.60f,  4.0f, 0.0f,   0.0f, 1.0f, 0.0f
};

GLuint planeIndices[] =
{
    0, 1, 2, 0, 2, 3
};

GLfloat lightVertices[] =
{ // COORDINATES
    -0.1f, -0.1f,  0.1f,
    -0.1f, -0.1f, -0.1f,
     0.1f, -0.1f, -0.1f,
     0.1f, -0.1f,  0.1f,
    -0.1f,  0.1f,  0.1f,
    -0.1f,  0.1f, -0.1f,
     0.1f,  0.1f, -0.1f,
     0.1f,  0.1f,  0.1f
};

GLuint lightIndices[] =
{
    0, 1, 2, 0, 2, 3,
    4, 5, 6, 4, 6, 7,
    0, 1, 5, 0, 5, 4,
    2, 3, 7, 2, 7, 6,
    1, 2, 6, 1, 6, 5,
    0, 3, 7, 0, 7, 4
};

static void framebufferSizeCallback(GLFWwindow* window, int width, int height)
{
    if (width <= 0 || height <= 0)
        return;

    glViewport(0, 0, width, height);
    Camera* camera = static_cast<Camera*>(glfwGetWindowUserPointer(window));
    if (camera)
    {
        camera->width = width;
        camera->height = height;
    }
}

int main()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_STENCIL_BITS, 8);

    GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "Lab9 - Lighting", NULL, NULL);
    if (!window) { glfwTerminate(); return -1; }
    glfwMakeContextCurrent(window);
    glfwSetWindowAttrib(window, GLFW_FOCUS_ON_SHOW, GLFW_TRUE);
    glfwFocusWindow(window);
    glfwSetInputMode(window, GLFW_STICKY_KEYS, GLFW_TRUE);
    glfwSetInputMode(window, GLFW_STICKY_MOUSE_BUTTONS, GLFW_TRUE);

    gladLoadGL(glfwGetProcAddress);
    glViewport(0, 0, WIDTH, HEIGHT);

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_STENCIL_TEST);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);

    Shader shaderProgram("shaders/default.vert", "shaders/default.frag");
    Shader lightShader("shaders/light.vert", "shaders/light.frag");

    VAO pyramidVAO;
    pyramidVAO.Bind();
    VBO pyramidVBO(pyramidVertices, sizeof(pyramidVertices));
    EBO pyramidEBO(pyramidIndices, sizeof(pyramidIndices));
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 11 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 11 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 11 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 11 * sizeof(float), (void*)(8 * sizeof(float)));
    glEnableVertexAttribArray(3);
    pyramidVAO.Unbind();
    pyramidVBO.Unbind();
    pyramidEBO.Unbind();

    VAO planeVAO;
    planeVAO.Bind();
    VBO planeVBO(planeVertices, sizeof(planeVertices));
    EBO planeEBO(planeIndices, sizeof(planeIndices));
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 11 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 11 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 11 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 11 * sizeof(float), (void*)(8 * sizeof(float)));
    glEnableVertexAttribArray(3);
    planeVAO.Unbind();
    planeVBO.Unbind();
    planeEBO.Unbind();

    VAO lightVAO;
    lightVAO.Bind();
    VBO lightVBO(lightVertices, sizeof(lightVertices));
    EBO lightEBO(lightIndices, sizeof(lightIndices));
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    lightVAO.Unbind();
    lightVBO.Unbind();
    lightEBO.Unbind();

    Texture popCat("textures/pop_cat.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
    popCat.texUnit(shaderProgram, "tex0", 0);

    Camera camera(WIDTH, HEIGHT, glm::vec3(0.0f, 0.7f, 2.8f));
    glfwSetWindowUserPointer(window, &camera);
    glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);

    glm::vec4 lightColor(1.0f, 0.8f, 0.7f, 1.0f);

    const glm::vec3 objectPositions[] = {
        glm::vec3(-1.2f, 0.2f, 0.0f),
        glm::vec3( 0.0f, 0.2f, 0.0f),
        glm::vec3( 1.2f, 0.2f, 0.0f)
    };
    const int lightingModes[] = { 0, 1, 2 };

    GLuint modelLoc = glGetUniformLocation(shaderProgram.ID, "model");
    GLuint lightColorLoc = glGetUniformLocation(shaderProgram.ID, "lightColor");
    GLuint lightPosLoc = glGetUniformLocation(shaderProgram.ID, "lightPos");
    GLuint camPosLoc = glGetUniformLocation(shaderProgram.ID, "camPos");
    GLuint lightingModeLoc = glGetUniformLocation(shaderProgram.ID, "lightingMode");

    GLuint lightModelLoc = glGetUniformLocation(lightShader.ID, "model");
    GLuint lightColorLightLoc = glGetUniformLocation(lightShader.ID, "lightColor");

    while (!glfwWindowShouldClose(window))
    {
        glEnable(GL_STENCIL_TEST);
        glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

        camera.Inputs(window);
        camera.updateMatrix(45.0f, 0.1f, 100.0f);

        float time = static_cast<float>(glfwGetTime());
        glm::vec3 lightPos(
            1.2f * std::sin(time),
            0.8f,
            1.2f * std::cos(time)
        );
        glm::mat4 lightModel = glm::translate(glm::mat4(1.0f), lightPos);

        lightShader.Activate();
        camera.Matrix(lightShader, "camMatrix");
        glUniformMatrix4fv(lightModelLoc, 1, GL_FALSE, glm::value_ptr(lightModel));
        glUniform4f(lightColorLightLoc, lightColor.r, lightColor.g, lightColor.b, lightColor.a);

        shaderProgram.Activate();
        camera.Matrix(shaderProgram, "camMatrix");
        glUniform4f(lightColorLoc, lightColor.r, lightColor.g, lightColor.b, lightColor.a);
        glUniform3f(lightPosLoc, lightPos.x, lightPos.y, lightPos.z);
        glUniform3f(camPosLoc, camera.Position.x, camera.Position.y, camera.Position.z);

        glActiveTexture(GL_TEXTURE0);
        popCat.Bind();

        glm::mat4 planeModel = glm::mat4(1.0f);

        // 1) Rysowanie szablonu lustra
        glColorMask(GL_FALSE, GL_FALSE, GL_FALSE, GL_FALSE);
        glDepthMask(GL_FALSE);
        glStencilMask(0xFF);
        glStencilFunc(GL_ALWAYS, 1, 0xFF);

        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(planeModel));
        glUniform1i(lightingModeLoc, 0);
        planeVAO.Bind();
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        // 2) Rysowanie odbicia w obszarze szablonu
        glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);
        glDepthMask(GL_TRUE);
        glStencilFunc(GL_EQUAL, 1, 0xFF);
        glStencilMask(0x00);

        glFrontFace(GL_CW);
        pyramidVAO.Bind();
        for (int i = 0; i < 3; ++i)
        {
            glm::mat4 model = glm::mat4(1.0f);
            model = glm::translate(model, objectPositions[i]);
            model = glm::scale(model, glm::vec3(1.0f, -1.0f, 1.0f));
            glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
            glUniform1i(lightingModeLoc, lightingModes[i]);
            glDrawElements(GL_TRIANGLES, 18, GL_UNSIGNED_INT, 0);
        }
        glFrontFace(GL_CCW);

        // 3) Rysowanie rzeczywistej sceny
        glStencilMask(0xFF);
        glDisable(GL_STENCIL_TEST);

        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(planeModel));
        glUniform1i(lightingModeLoc, 1);
        planeVAO.Bind();
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        pyramidVAO.Bind();
        for (int i = 0; i < 3; ++i)
        {
            glm::mat4 model = glm::mat4(1.0f);
            model = glm::translate(model, objectPositions[i]);
            glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
            glUniform1i(lightingModeLoc, lightingModes[i]);
            glDrawElements(GL_TRIANGLES, 18, GL_UNSIGNED_INT, 0);
        }

        lightShader.Activate();
        camera.Matrix(lightShader, "camMatrix");
        glUniformMatrix4fv(lightModelLoc, 1, GL_FALSE, glm::value_ptr(lightModel));
        glUniform4f(lightColorLightLoc, lightColor.r, lightColor.g, lightColor.b, lightColor.a);
        lightVAO.Bind();
        glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    popCat.Delete();
    pyramidVAO.Delete();
    pyramidVBO.Delete();
    pyramidEBO.Delete();
    planeVAO.Delete();
    planeVBO.Delete();
    planeEBO.Delete();
    lightVAO.Delete();
    lightVBO.Delete();
    lightEBO.Delete();
    shaderProgram.Delete();
    lightShader.Delete();
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}
