#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <spdlog/spdlog.h>

using namespace std;

class Texture {
private:
    GLuint _texture;

    shared_ptr<spdlog::logger> _log;
public:
    Texture(shared_ptr<spdlog::logger> log);
    ~Texture();

    bool Init(string path);

    void Use(bool state = true);

    GLuint native_texture();
};