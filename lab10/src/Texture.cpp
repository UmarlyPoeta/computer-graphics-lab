#include "Texture.h"
#include <iostream>


Texture::Texture(const char* image, GLenum texType, GLenum slot, GLenum format, GLenum pixelType) {
    type = texType;
    (void)format;

    int widthImg = 0;
    int heightImg = 0;
    int numColCh = 0;

    stbi_set_flip_vertically_on_load(true);
    unsigned char* bytes = stbi_load(image, &widthImg, &heightImg, &numColCh, STBI_rgb_alpha);
    const unsigned char* pixelData = bytes;
    bool usingFallback = false;

    if (!bytes)
    {
        std::cerr << "Failed to load texture: " << image;
        const char* reason = stbi_failure_reason();
        if (reason)
        {
            std::cerr << " (" << reason << ")";
        }
        std::cerr << std::endl;

        static const unsigned char fallbackPixel[4] = { 255, 0, 255, 255 };
        pixelData = fallbackPixel;
        widthImg = 1;
        heightImg = 1;
        usingFallback = true;
    }

    glGenTextures(1, &ID);
    glActiveTexture(slot);
    glBindTexture(texType, ID);

    glTexParameteri(texType, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);
    glTexParameteri(texType, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    glTexParameteri(texType, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(texType, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glTexImage2D(texType, 0, GL_RGBA, widthImg, heightImg, 0, GL_RGBA, pixelType, pixelData);
    glGenerateMipmap(texType);

    if (!usingFallback)
    {
        stbi_image_free(bytes);
    }
    glBindTexture(texType, 0);
}

void Texture::texUnit(Shader& shader, const char* uniform, GLuint unit) {
    GLuint texUni = glGetUniformLocation(shader.ID, uniform);
    shader.Activate();
    glUniform1i(texUni, unit);
}

void Texture::Bind() {
    glBindTexture(type, ID);
}

void Texture::Unbind() {
    glBindTexture(type, 0);
}

void Texture::Delete() {
    glDeleteTextures(1, &ID);
}
