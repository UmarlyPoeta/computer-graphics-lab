#include "Camera.h"

Camera::Camera(int width, int height, glm::vec3 positon) {
    Camera::width = width;
    Camera::height = height;
    Camera::position = position;
}

Camera::Matrix(float FOVdeg, float nearPlane, float farPlane, Shader* shader, const char* uniform) {
    
}