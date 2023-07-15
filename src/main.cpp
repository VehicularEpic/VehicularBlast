#include "veb/gui/Window.hpp"
#include "veb/io/MeshBank.hpp"

#include <glad/gl.h>

static constexpr const char *models[] = {
        "prod", "prodw", "prodb2", "prodb1", "prodt", "drod", "grod", "drodt", "nrod", "nrodt",
        "mixpd", "mixnd", "mixpn", "prode", "drode", "pipg", "prmp", "prmpc", "prmpg", "prmpm",
        "prmpw", "prmpb", "prmps", "dbmp", "drmpb", "drmps", "pipe", "spikes", "rail", "brdr",
        "chk", "fix", "dchk", "drodb", "drodbb", "bprmpup", "prmpup", "start", "wall", "fenc",
        "prmpl", "net", "prmpspd", "drmpg", "tiny", "dhil", "stunl", "tunl", "lift", "mountn",
        "mass", "cres", "pile1", "pile2", "brdr2", "tre1", "tre2", "tre3", "tre4", "tre5",
        "tre6", "tre7", "tre8", "cac1", "cac2", "cac3", "blok", "full", "pyrmd", "tub"};

static constexpr const char *vehicles[] = {
        "drags", "destroy"};

int main(int argc, char const *argv[]) {
    veb::Window window("Vehicular Blast");

    glEnable(GL_CULL_FACE);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);

    veb::MeshBank meshes("assets/models");
    for (const char *name : vehicles)
        meshes.Load(name);

    for (const char *name : models)
        meshes.Load(name);

    while (window.IsActive()) {
        window.Clear();
        window.Update();
    }

    return 0;
}
