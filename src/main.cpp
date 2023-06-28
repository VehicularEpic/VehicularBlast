#include "gui/Window.hpp"

int main(int argc, char const *argv[]) {
    veb::Window window("Vehicular Blast");

    while (window.IsActive())
        window.Update();

    return 0;
}
