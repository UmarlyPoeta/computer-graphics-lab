#include <iostream>
#include <glad/gl.h>
#include <GLFW/glfw3.h>

const char* vertexShaderSource =
"#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"layout (location = 1) in vec3 aColor;\n"
"out vec3 ourColor;\n"
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos,1.0);\n"
"   ourColor = aColor;\n"
"}\n";

const char* fragmentShaderSource =
"#version 330 core\n"
"in vec3 ourColor;\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"   FragColor = vec4(ourColor,1.0);\n"
"}\n";

int main()
{
    const int i = 10;
    const int j = 10;

    glfwInit();

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR,3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR,3);
    glfwWindowHint(GLFW_OPENGL_PROFILE,GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(800,800,"Szachownica",NULL,NULL);

    glfwMakeContextCurrent(window);
    gladLoadGL(glfwGetProcAddress);

    glViewport(0,0,800,800);

    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader,1,&vertexShaderSource,NULL);
    glCompileShader(vertexShader);

    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader,1,&fragmentShaderSource,NULL);
    glCompileShader(fragmentShader);

    GLuint shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram,vertexShader);
    glAttachShader(shaderProgram,fragmentShader);
    glLinkProgram(shaderProgram);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    const int squares = i*j;

    GLfloat vertices[squares * 4 * 6];
    GLuint indices[squares * 6];

    float w = 2.0f / i;
    float h = 2.0f / j;

    int vk = 0;
    int ik = 0;
    int base = 0;

    for(int r=0;r<j;r++)
    {
        for(int d=0;d<i;d++)
        {
            float x = -1.0f + d*w;
            float y =  1.0f - (r+1)*h;

            float color = (r+d)%2;

            float rcol = color ? 1.0f : 0.0f;
            float gcol = color ? 1.0f : 0.0f;
            float bcol = color ? 1.0f : 0.0f;

            // A
            vertices[vk++] = x;
            vertices[vk++] = y;
            vertices[vk++] = 0;

            vertices[vk++] = rcol;
            vertices[vk++] = gcol;
            vertices[vk++] = bcol;

            // B
            vertices[vk++] = x+w;
            vertices[vk++] = y;
            vertices[vk++] = 0;

            vertices[vk++] = rcol;
            vertices[vk++] = gcol;
            vertices[vk++] = bcol;

            // C
            vertices[vk++] = x+w;
            vertices[vk++] = y+h;
            vertices[vk++] = 0;

            vertices[vk++] = rcol;
            vertices[vk++] = gcol;
            vertices[vk++] = bcol;

            // D
            vertices[vk++] = x;
            vertices[vk++] = y+h;
            vertices[vk++] = 0;

            vertices[vk++] = rcol;
            vertices[vk++] = gcol;
            vertices[vk++] = bcol;

            indices[ik++] = base;
            indices[ik++] = base+1;
            indices[ik++] = base+2;

            indices[ik++] = base;
            indices[ik++] = base+2;
            indices[ik++] = base+3;

            base += 4;
        }
    }

    GLuint VAO,VBO,EBO;

    glGenVertexArrays(1,&VAO);
    glGenBuffers(1,&VBO);
    glGenBuffers(1,&EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER,VBO);
    glBufferData(GL_ARRAY_BUFFER,sizeof(vertices),vertices,GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,sizeof(indices),indices,GL_STATIC_DRAW);

    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,6*sizeof(float),(void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1,3,GL_FLOAT,GL_FALSE,6*sizeof(float),(void*)(3*sizeof(float)));
    glEnableVertexAttribArray(1);

    while(!glfwWindowShouldClose(window))
    {
        glClearColor(0.07f,0.13f,0.17f,1);
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(shaderProgram);
        glBindVertexArray(VAO);

        glDrawElements(GL_TRIANGLES, squares*6, GL_UNSIGNED_INT, 0);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
}