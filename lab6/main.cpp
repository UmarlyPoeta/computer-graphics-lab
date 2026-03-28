#include <iostream>
#include <glad/gl.h>
#include <GLFW/glfw3.h>

const char* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 position;\n"
"layout (location = 1) in vec3 color;\n"
"out vec3 Color;\n"
"void main()\n"
"{\n"
"   Color = color;\n"
"   gl_Position = vec4(position, 1.0);\n"
"}\0";

const char* fragmentShaderSource = "#version 330 core\n"
"in vec3 Color;\n"
"out vec4 outColor;\n"
"void main()\n"
"{\n"
"   outColor = vec4(Color, 1.0);\n"
"}\n\0";


int main()
{
    const int i = 10;
    const int j = 10;

    // INIT GLFW
    if (!glfwInit())
        return -1;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR,3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR,3);
    glfwWindowHint(GLFW_OPENGL_PROFILE,GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(800,800,"Szachownica",NULL,NULL);
    if (!window)
        return -1;

    glfwMakeContextCurrent(window);

    // INIT GLAD
    if (!gladLoadGL(glfwGetProcAddress))
        return -1;

    glViewport(0,0,800,800);

    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader,1,&vertexShaderSource,NULL);
    glCompileShader(vertexShader);

    int success;
    char infoLog[512];

    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if(!success)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << "Vertex shader ERROR:\n" << infoLog << std::endl;
    }
    else std::cout << "Vertex shader OK\n";

    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader,1,&fragmentShaderSource,NULL);
    glCompileShader(fragmentShader);

    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if(!success)
    {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        std::cout << "Fragment shader ERROR:\n" << infoLog << std::endl;
    }
    else std::cout << "Fragment shader OK\n";

    GLuint shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram,vertexShader);
    glAttachShader(shaderProgram,fragmentShader);
    glLinkProgram(shaderProgram);

    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if(!success)
    {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        std::cout << "Shader program ERROR:\n" << infoLog << std::endl;
    }
    else std::cout << "Shader program OK\n";

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
            vertices[vk++] = 0.0f;
            vertices[vk++] = rcol;
            vertices[vk++] = gcol;
            vertices[vk++] = bcol;

            // B
            vertices[vk++] = x+w;
            vertices[vk++] = y;
            vertices[vk++] = 0.0f;
            vertices[vk++] = rcol;
            vertices[vk++] = gcol;
            vertices[vk++] = bcol;

            // C
            vertices[vk++] = x+w;
            vertices[vk++] = y+h;
            vertices[vk++] = 0.0f;
            vertices[vk++] = rcol;
            vertices[vk++] = gcol;
            vertices[vk++] = bcol;

            // D
            vertices[vk++] = x;
            vertices[vk++] = y+h;
            vertices[vk++] = 0.0f;
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
        glClearColor(0.07f,0.13f,0.17f,1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(shaderProgram);
        glBindVertexArray(VAO);

        glDrawElements(GL_TRIANGLES, squares*6, GL_UNSIGNED_INT, 0);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }


    glDeleteVertexArrays(1,&VAO);
    glDeleteBuffers(1,&VBO);
    glDeleteBuffers(1,&EBO);
    glDeleteProgram(shaderProgram);

    glfwTerminate();
    return 0;
}