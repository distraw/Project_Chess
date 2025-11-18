#include "vbo.h"

VBO::VBO(shared_ptr<spdlog::logger> log) {
    _log = log;
}

VBO::~VBO() {
    if (!_vbo) {
        _log->error("attempted to delete non-existent vertex buffer object");
        return;
    }

    _log->trace("deleting vertex buffer object {0}...", _vbo);
    glDeleteBuffers(1, &_vbo);
}

void VBO::Init(GLfloat* vertex_buffer, GLsizeiptr size) {
    glGenBuffers(1, &_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, _vbo);
    glBufferData(GL_ARRAY_BUFFER, size * sizeof(float), vertex_buffer, GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, NULL);
    _log->trace("initialized vertex buffer object {0}", _vbo);
}

GLuint VBO::native_vbo() {
    return _vbo;
}