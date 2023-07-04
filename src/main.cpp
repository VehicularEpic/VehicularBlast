#include "gui/Window.hpp"

#include <glad/gl.h>

int main(int argc, char const *argv[]) {
    veb::Window window("Vehicular Blast");

    glEnable(GL_CULL_FACE);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);

    while (window.IsActive()) {
        window.Clear();
        window.Update();
    }

    return 0;
}
