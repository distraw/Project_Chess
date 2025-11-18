#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "texture.h"
#include "vao.h"
#include "vbo.h"

#include <spdlog/spdlog.h>

class Sprite {
private:
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