#include "veb/gui/Window.hpp"

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <glad/gl.h>

#include <cstdio>

static void ErrorCallback(int error, const char *description) {
    fprintf(stderr, "GLFW Error: %s (%d)\n", description, error);
}

namespace veb {

template<>
void Window::FramebufferSizeCallback(GLFWwindow *window, int w, int h) {
    if (w <= 0 || h <= 0)
        return;

    glViewport(0, 0, w, h);

    auto instance = static_cast<Window *>(glfwGetWindowUserPointer(window));
    for (const FramebufferSizeCallbackFn &listener : instance->framebufferSizeListeners)
        listener(w, h);
}

template<>
void Window::WindowSizeCallback(GLFWwindow *window, int w, int h) {
    auto instance = static_cast<Window *>(glfwGetWindowUserPointer(window));
    instance->width = w;
    instance->height = h;
}

template<>
void Window::KeyCallback(GLFWwindow *window, int key, int scancode, int action, int mods) {
    if (action == GLFW_REPEAT)
        return;

    auto instance = static_cast<Window *>(glfwGetWindowUserPointer(window));
    for (const KeyCallbackFn &callback : instance->keyListeners)
        callback(key, action == GLFW_PRESS);
}

Window::Window(const std::string &name) {
    glfwSetErrorCallback(ErrorCallback);

    if (!glfwInit())
        exit(EXIT_FAILURE);

    glfwDefaultWindowHints();
    glfwWindowHint(GLFW_SAMPLES, 4);

    glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE);

    handle = glfwCreateWindow(width, height, name.c_str(), nullptr, nullptr);

    if (!handle) {
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    glfwSetWindowUserPointer(static_cast<GLFWwindow *>(handle), this);
    glfwSetInputMode(static_cast<GLFWwindow *>(handle), GLFW_LOCK_KEY_MODS, GLFW_TRUE);
    glfwMakeContextCurrent(static_cast<GLFWwindow *>(handle));

    gladLoadGL(glfwGetProcAddress);
    glClearColor(0.f, 0.f, 0.f, 1.f);
    glViewport(0, 0, width, height);

    glfwSetFramebufferSizeCallback(static_cast<GLFWwindow *>(handle), Window::FramebufferSizeCallback);
    glfwSetWindowSizeCallback(static_cast<GLFWwindow *>(handle), Window::WindowSizeCallback);

    glfwSetKeyCallback(static_cast<GLFWwindow *>(handle), Window::KeyCallback);

    glfwShowWindow(static_cast<GLFWwindow *>(handle));
}

Window::~Window() {
    glfwDestroyWindow(static_cast<GLFWwindow *>(handle));
}

void Window::SetWidth(int w) {
    width = w;
    glfwSetWindowSize(static_cast<GLFWwindow *>(handle), width, height);
}

void Window::SetHeight(int h) {
    height = h;
    glfwSetWindowSize(static_cast<GLFWwindow *>(handle), width, height);
}

bool Window::IsActive() const {
    return !glfwWindowShouldClose(static_cast<GLFWwindow *>(handle));
}

double Window::GetTime() const {
    return glfwGetTime();
}

void Window::Clear() const {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Window::Update() const {
    glfwSwapBuffers(static_cast<GLFWwindow *>(handle));
    glfwPollEvents();
}

} // namespace veb
