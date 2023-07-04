#include "Window.hpp"

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
    glViewport(0, 0, w, h);

    auto instance = static_cast<Window *>(glfwGetWindowUserPointer(window));
    for (const FramebufferSizeCallbackFn &listener : instance->framebufferSizeListeners)
        listener(w, h);
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
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

#if defined(OS_MAC)
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE);
#endif

    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    handle = glfwCreateWindow(800, 600, name.c_str(), nullptr, nullptr);

    if (!handle) {
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    glfwSetWindowUserPointer(static_cast<GLFWwindow *>(handle), this);
    glfwSetInputMode(static_cast<GLFWwindow *>(handle), GLFW_LOCK_KEY_MODS, GLFW_TRUE);
    glfwMakeContextCurrent(static_cast<GLFWwindow *>(handle));

    gladLoadGL(glfwGetProcAddress);
    glClearColor(0.f, 0.f, 0.f, 1.f);
    glViewport(0, 0, 800, 600);

    glfwSetFramebufferSizeCallback(static_cast<GLFWwindow *>(handle), Window::FramebufferSizeCallback);
    glfwShowWindow(static_cast<GLFWwindow *>(handle));
}

Window::~Window() {
    glfwDestroyWindow(static_cast<GLFWwindow *>(handle));
}

int Window::GetWidth() const {
    int width = 0;
    glfwGetWindowSize(static_cast<GLFWwindow *>(handle), &width, NULL);

    return width;
}

void Window::SetWidth(int width) {
    glfwSetWindowSize(static_cast<GLFWwindow *>(handle), width, GetHeight());
}

int Window::GetHeight() const {
    int height = 0;
    glfwGetWindowSize(static_cast<GLFWwindow *>(handle), NULL, &height);

    return height;
}

void Window::SetHeight(int height) {
    glfwSetWindowSize(static_cast<GLFWwindow *>(handle), GetWidth(), height);
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
