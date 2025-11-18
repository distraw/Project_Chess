#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <spdlog/spdlog.h>

using namespace std;

class VBO {
private:
    GLuint _vbo;

    shared_ptr<spdlog::logger> _log;
public:
    VBO(shared_ptr<spdlog::logger> log);
    ~VBO();

    void Init(GLfloat* vertex_buffer, GLsizeiptr size);

    GLuint native_vbo();
};