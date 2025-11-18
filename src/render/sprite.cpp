#include "sprite.h"

namespace render {

Sprite::Sprite(shared_ptr<spdlog::logger> log) {
    _log = log;
}

Sprite::~Sprite() {
    delete _texture;
    delete _vao;
    delete _vbo;
    delete _tbo;

    _log->trace("deleting sprite...");
}

bool Sprite::Init(string texture_source, float width, float height) {
    _x = 0;
    _y = 0;

    _vao = new VAO(_log);
    _vao->Init();

    float vertices[]{
        0, 0,
        width, 0,
        width, height,
        0, height
    };
    float texcoord[]{0, 1, 1, 1, 1, 0, 0, 0};

    _vbo = new VBO(_log);
    _vbo->Init(vertices, sizeof(vertices));

    _tbo = new VBO(_log);
    _tbo->Init(texcoord, sizeof(texcoord));

    _vao->Attach(_vbo->native_vbo(), 0);
    _vao->Attach(_tbo->native_vbo(), 1);

    _texture = new Texture(_log);
    if (!_texture->Init(texture_source)) {
        _log->critical("failed to load texture");
        return false;
    }
    return true;
}

void Sprite::AttachProgram(GLuint shader_program) {
    _shader_program = shader_program;
}

void Sprite::SetPosition(float x, float y) {
    _x = x;
    _y = y;
}

void Sprite::Draw() {
    glUniform2f(glGetUniformLocation(_shader_program, "pos"), _x, _y);

    _vao->Use();
    _texture->Use();

    glDrawArrays(GL_TRIANGLE_FAN, 0, 4);

    _texture->Use(false);
    _vao->Use(false);
}

}