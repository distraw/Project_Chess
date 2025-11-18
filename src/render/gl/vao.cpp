#include "vao.h"

VAO::VAO(shared_ptr<spdlog::logger> log) {
    _log = log;
}

VAO::~VAO() {
    if (!_vao) {
        _log->error("attempted to delete non-existent vertex array object");
        return;
    }

    _log->trace("deleting vertex array object {0}...", _vao);
    glDeleteVertexArrays(1, &_vao);
}

void VAO::Init() {
    glGenVertexArrays(1, &_vao);
    _log->trace("initialized vertex array object {0}", _vao);
}

void VAO::Attach(GLuint vbo, GLuint index) {
    glBindVertexArray(_vao);

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glVertexAttribPointer(index, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);
    glEnableVertexAttribArray(index);
    _log->trace("attached VBO {0} to VAO {1}", vbo, _vao);

    glBindVertexArray(0);
}

void VAO::Use(bool state) {
    glBindVertexArray(state ? _vao : 0);
}

GLuint VAO::native_vao() {
    return _vao;
}