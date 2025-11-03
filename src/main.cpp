#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>

#include "core/window.h"
#include "core/shader.h"
#include "core/program.h"

#include "render/texture.h"
#include "render/vao.h"
#include "render/vbo.h"

#include "util/config.h"

int main() {
    auto log = spdlog::stdout_color_mt("stdout");
    log->set_level(spdlog::level::trace);

    Config config(log);
    if (!config.Init("./settings.json")) {
        log->critical("failed to initialize config");
        return -1;
    }

    Window window(log);
    if (!window.Init(config.window_width(), config.window_height(), "Distraw Chess")) {
        log->critical("failed to open window");
        return -1;
    }

    Shader vertex_shader(log);
    if (!vertex_shader.Load("./shader/vertex.glsl", GL_VERTEX_SHADER)) {
        log->critical("failed to load vertex shader");
        return -1;
    }

    Shader fragment_shader(log);
    if (!fragment_shader.Load("./shader/fragment.glsl", GL_FRAGMENT_SHADER)) {
        log->critical("failed to load fragment shader");
        return -1;
    }

    Program program(log);
    if (!program.Init(vertex_shader.native_shader(), fragment_shader.native_shader())) {
        log->critical("failed to load program");
        return -1;
    }

    program.Use();

    VAO vao(log);
    vao.Init();
    
    float vertices[]{-1.f, -1.f, 1.f, -1.f, 1.f, 1.f, -1.f, 1.f};
    float texcoord[]{0, 0, 1, 0, 1, 1, 0, 1};

    VBO vbo(log);
    vbo.Init(vertices, sizeof(vertices));

    VBO tbo(log);
    tbo.Init(texcoord, sizeof(texcoord));

    vao.Attach(vbo.native_vbo(), 0);
    vao.Attach(tbo.native_vbo(), 1);

    Texture texture(log);
    if (!texture.Init("texture/board.jpg")) {
        log->critical("failed to load texture");
        return -1;
    }

    window.ChangeBackgroundColor(0, 0, 0);
    while (window.IsOpened()) {
        window.Refresh();
        glfwPollEvents();

        program.Use();
        vao.Use();
        texture.Use();
        glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
        texture.Use(false);
        vao.Use(false);
    }

    return 0;
}