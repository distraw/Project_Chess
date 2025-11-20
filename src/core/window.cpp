#include "window.h"

Window::Window(shared_ptr<spdlog::logger> log) {
    _log = log;
}

Window::~Window() {
    if (_window == nullptr) {
        _log->error("attempted to delete non-existent window");
        return;
    }

    _log->trace("closing window...");
    glfwDestroyWindow(_window);

    _log->trace("terminating GLFW...");
    glfwTerminate();
}

bool Window::Init(int width, int height, string title) {
    _title = title;
    _width  = width;
    _height = height;

    if (glfwInit() == GLFW_FALSE) {
        _log->critical("failed to initialize GLFW");
        return false;
    }
    _log->trace("initialized GLFW");

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    _log->info("MacOS is detected. Appropriate changes were made for window");
#endif

    _window = glfwCreateWindow(_width, _height, _title.c_str(), nullptr, nullptr);
    glfwMakeContextCurrent(_window);
    if (_window == nullptr) {
        _log->critical("failed to open window");
        const char* err;
        glfwGetError(&err);
        _log->critical(err);
        
        return false;
    }
    _log->trace("initialized window");

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
        _log->critical("failed to initialize GLAD");
        return false;
    }
    _log->trace("initialized GLAD");

    return true;
}

void Window::Refresh() {
    glfwSwapBuffers(_window);
    glClear(GL_COLOR_BUFFER_BIT);
}

void Window::ChangeBackgroundColor(GLfloat r, GLfloat g, GLfloat b) {
    glClearColor(r, g, b, 0.f);
}

bool Window::IsOpened() {
    return !glfwWindowShouldClose(_window);
}

int Window::width() {
    return _width;
}

int Window::height() {
    return _height;
}

string Window::title() {
    return _title;
}

GLFWwindow* Window::native_window() {
    return _window;
}