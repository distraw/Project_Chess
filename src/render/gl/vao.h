#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <spdlog/spdlog.h>

using namespace std;

class VAO {
private:
    GLuint _vao;

    shared_ptr<spdlog::logger> _log;
public:
    VAO(shared_ptr<spdlog::logger> log);
    ~VAO();
    
    void Init();

    void Attach(GLuint vbo, GLuint index);
    void Use(bool state = true);

    GLuint native_vao();
};