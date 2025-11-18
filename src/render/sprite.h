#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "gl/texture.h"
#include "gl/vao.h"
#include "gl/vbo.h"

#include <spdlog/spdlog.h>

namespace render {

class Sprite {
protected:
    Texture* _texture;

    VAO* _vao;

    VBO* _vbo;
    VBO* _tbo;

    GLuint _shader_program;

    float _x;
    float _y;

    shared_ptr<spdlog::logger> _log;
public:
    Sprite(shared_ptr<spdlog::logger> log);
    ~Sprite();

    bool Init(string texture_source, float width, float height);
    void AttachProgram(GLuint shader_program);

    void SetPosition(float x, float y);

    void Draw();
};

}