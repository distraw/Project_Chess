#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>

#include "core/window.h"
#include "core/shader.h"
#include "core/program.h"

#include "render/board.h"

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

    render::Board board(log);
    if (!board.Init(program.native_program())) {
        log->critical("failed to load rendering board");
        return -1;
    }
    
    board.Move(4, 1, 4, 3);
    board.Move(4, 6, 4, 4);
    board.Move(6, 0, 5, 2);
    board.Move(1, 7, 2, 5);
    board.Move(5, 0, 2, 3);

    program.Use();
    window.ChangeBackgroundColor(1, 0, 0);
    while (window.IsOpened()) {
        window.Refresh();
        glfwPollEvents();

        board.Draw();
    }

    return 0;
}