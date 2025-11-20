#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>

#include "core/shader.h"
#include "core/program.h"

#include "input.h"

#include <cstdio>

#include "util/config.h"

class CatchExit {
    shared_ptr<spdlog::logger> _log;
public:
    CatchExit(shared_ptr<spdlog::logger> log) {
        _log = log;
    }
    ~CatchExit() {
        _log->info("Program exited. Press any key to continue...");
        getchar();
    }
};

int main() {
    auto log = spdlog::stdout_color_mt("stdout");
    log->set_level(spdlog::level::trace);
    
    CatchExit t(log);

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
    
    program.Use();
    window.ChangeBackgroundColor(1, 0, 0);
    while (window.IsOpened()) {
        std::this_thread::sleep_for(std::chrono::milliseconds(10));

        window.Refresh();
        glfwPollEvents();

        ProcessInput(log, &window, &board);

        board.Draw();
    }

    return 0;
}