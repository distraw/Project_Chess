#include "texture.h"

// Necessary to declare in order to stb_image to be able to load images
#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>

Texture::Texture(shared_ptr<spdlog::logger> log) {
    _log = log;
}

Texture::~Texture() {
    if (!_texture) {
        _log->error("attempted to delete non-existent texture");
        return;
    }

    _log->trace("deleting texture {0}", _texture);
    glDeleteTextures(1, &_texture);
}

bool Texture::Init(string path) {
    // nr_channels stands for number of color channels per pixel (usually RGB, or RGB+Alpha)
    int width, height, nr_channels;
    unsigned char* source = stbi_load(path.c_str(), &width, &height, &nr_channels, STBI_rgb_alpha);
    if (!source) {
        _log->critical("failed to load {0} into texture", path);
        return false;
    }
    _log->trace("loaded texture source {0}", path);

    glGenTextures(1, &_texture);
    glBindTexture(GL_TEXTURE_2D, _texture);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    GLint channel_type = GL_RGBA;
    glTexImage2D(GL_TEXTURE_2D, 0, channel_type, width, height,
                0, channel_type, GL_UNSIGNED_BYTE, source);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    return true;
}

void Texture::Use(bool state) {
    glActiveTexture(0);
    glBindTexture(GL_TEXTURE_2D, state == true ? _texture : 0);
}

GLuint Texture::native_texture() {
    return _texture;
}