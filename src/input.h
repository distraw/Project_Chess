#pragma once

#include <GLFW/glfw3.h>

#include "render/board.h"
#include "core/window.h"

bool start_chosen = false;
bool mouse_down = false;

unsigned int old_x;
unsigned int old_y;
unsigned int new_x;
unsigned int new_y;

void ProcessInput(shared_ptr<spdlog::logger> log, Window* window, render::Board* board) {
    GLFWwindow* nw = window->native_window();

    if (glfwGetMouseButton(nw, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) {
        mouse_down = true;
    }
    else {
        if (mouse_down) {
            double xpos, ypos;
            glfwGetCursorPos(nw, &xpos, &ypos);

            if (!start_chosen) {
                start_chosen = true;

                old_x = xpos / window->width() * BOARD_SIZE;
                old_y = BOARD_SIZE - (ypos / window->height() * BOARD_SIZE);

                log->debug("old_x={0}, old_y={1}", old_x, old_y);
            }
            else {
                start_chosen = false;

                new_x = xpos / window->width() * BOARD_SIZE;
                new_y = BOARD_SIZE - (ypos / window->height() * BOARD_SIZE);

                log->debug("new_x={0}, new_y={1}", new_x, new_y);

                board->Move(old_x, old_y, new_x, new_y);
            }
        }

        mouse_down = false;
    }
}