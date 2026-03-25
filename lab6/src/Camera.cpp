#include "include/Camera.h"

Camera::Camera(int width, int height, glm::vec3 positon) {
    Camera::width = width;
    Camera::height = height;
    Camera::position = position;
}

Camera::Matrix(float FOVdeg, float nearPlane, float farPlane, Shader* shader, const char* uniform) {
    glm::mat4 view = glm::mat4(1.0f);
    glm::mat4 projection = glm::mat4(1.0f);

    view = glm::lookAt(Camera::position, Camera::position + Camera::orientation, Camera::up);
    projection = glm::perspective(glm::radians(FOVdeg), (float)width / height, nearPlane, farPlane);

}

void Camera::Inputs(GLFWindow* window) {
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
    {
    Position += speed * Orientation;
    }
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
    {
    Position += speed * -glm::normalize(glm::cross(Orientation, Up));
    }
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
    {
    Position += speed * -Orientation;
    }
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
    {
    Position += speed * glm::normalize(glm::cross(Orientation, Up));
    }
    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
    {
    Position += speed * Up;
    }
    if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
    {
    Position += speed * -Up;
    }
    if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
    {
    speed = 0.4f;
    }
    else if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_RELEASE)
    {
    speed = 0.1f;
    }


    if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) {
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);

        if (firstClick) {
            glfwSetCursorPos(window, (width / 2), (height / 2));
            firstClick = false;
        }


        double mouseX;
        double mouseY;

        glfwGetCursorPos(window, &mouseX, &mouseY);


        float rotX = sensitivity * (float)(mouseY - (height / 2)) / height;

        float rotY = sensitivity * (float)(mouseX - (width / 2)) / width;
    
        glm::vec3 newOrientation = glm::rotate(Camera::orientation, glm::radians(-rotX), glm::normalize(glm::cross(Camera::orientation, Camera::Up)));

        if (abs(glm::angle(newOrientation, Camera::Up) - glm::radians(90.0f)) <= glm::radians(85.0f))
        {
            Camera::orientation = newOrientation;
        }

        Camera::orientation = glm::rotate(Camera::orientation, glm::radius(-rotY), Camera::Up);

        glfwSetCursorPos(window, (width / 2), (height / 2));


    }
    else if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_RELEASE)
    {
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
        firstClick = true;
    }
}