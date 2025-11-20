#include "shader.h"

#include <sstream>
#include <fstream>

using namespace std;

Shader::Shader(shared_ptr<spdlog::logger> log) {
    _log = log;
}

Shader::~Shader() {
    if (!_shader) {
        _log->error("attempted to delete non-existent shader");
        return;
    }

    _log->trace("deleting shader {0}...", _shader);
    glDeleteShader(_shader);
}

bool Shader::Load(string path, GLenum type) {
    _type = type;

    ifstream file(path);
	if (!file.is_open()) {
        _log->critical("failed to open {0}", path);
        return false;
	}
    _log->trace("opened {0} for reading", path);

	stringstream buffer;
	buffer << file.rdbuf();
	_source = buffer.str();
    _log->trace("read from {0} into buffer successfully", path);

	_shader = glCreateShader(_type);

	const GLchar* cc_source = _source.c_str();
	glShaderSource(_shader, 1, &cc_source, nullptr);
	glCompileShader(_shader);

	GLint ok;
	glGetShaderiv(_shader, GL_COMPILE_STATUS, &ok);
	if (!ok) {
		GLchar infolog[1024];
		glGetShaderInfoLog(_shader, 1024, NULL, infolog);
        _log->critical("failed to compile shader: {0}", string(infolog));
        return false;
	}
    _log->trace("compiled shader {0} from {1}", _shader, path);

    file.close();
    return true;
}

GLuint Shader::native_shader() {
    return _shader;
}