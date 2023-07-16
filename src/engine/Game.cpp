#include "veb/engine/Game.hpp"

#include "veb/gfx/FragmentShader.hpp"
#include "veb/gfx/VertexShader.hpp"

#include <fstream>
#include <sstream>

#include <glad/gl.h>
#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>
#include <glm/ext/matrix_clip_space.hpp>

static constexpr const char *models[] = {
        "prod", "prodw", "prodb2", "prodb1", "prodt", "drod", "grod", "drodt", "nrod", "nrodt",
        "mixpd", "mixnd", "mixpn", "prode", "drode", "pipg", "prmp", "prmpc", "prmpg", "prmpm",
        "prmpw", "prmpb", "prmps", "dbmp", "drmpb", "drmps", "pipe", "spikes", "rail", "brdr",
        "chk", "fix", "dchk", "drodb", "drodbb", "bprmpup", "prmpup", "wall", "fenc",
        "prmpl", "net", "prmpspd", "drmpg", "tiny", "dhil", "stunl", "tunl", "lift", "mountn",
        "mass", "pile1", "pile2", "brdr2", "tre1", "tre2", "tre3", "tre4", "tre5",
        "tre6", "tre7", "tre8", "cac1", "cac2", "cac3", "blok", "pyrmd", "tub"};

static constexpr const char *vehicles[] = {
        "drags", "destroy"};


static veb::ShaderProgram CreateShader(std::string name) {
    veb::ShaderProgram shader;

    std::ifstream vs("assets/shaders/" + name + ".vs");
    std::stringstream vertex_source;
    vertex_source << vs.rdbuf();

    std::ifstream fs("assets/shaders/" + name + ".fs");
    std::stringstream fragment_source;
    fragment_source << fs.rdbuf();

    veb::VertexShader vertex(vertex_source.str());
    shader.Attach(vertex);

    veb::FragmentShader fragment(fragment_source.str());
    shader.Attach(fragment);

    shader.Link();
    return std::move(shader);
}

namespace veb {

Game::Game() : window("Vehicular Blast"), keyboard(window), meshBank("assets/models"), shader(CreateShader("main")) {
    glEnable(GL_CULL_FACE);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);

    for (const char *name : vehicles)
        meshBank.Load(name);

    for (const char *name : models)
        meshBank.Load(name);

    for (uint32_t i = 1; i <= 71; i++) {
        std::string mapFile = "assets/maps/" + std::to_string(i) + ".pbf";
        maps.push_back(Map(mapFile, meshBank));
    }

    auto SetPerspective = [&](int width, int height) {
        glm::mat4 projection = glm::perspective(70.f, width / (float) height, 0.1f, 10000.f);

        shader.Bind();
        shader.Matrix4x4f("projection", projection);
        shader.Unbind();
    };

    SetPerspective(window.GetWidth(), window.GetHeight());
    window.AddFramebufferSizeCallback(SetPerspective);

    shader.Bind();
    shader.Vec3("u_LightPos", glm::vec3(0.f, 100.f, -100.f));
    shader.Unbind();
}

void Game::Start() const {
    double before = 0;

    while (window.IsActive()) {
        double now = window.GetTime();
        double delta = now - before;
        before = now;

        window.Clear();
        if (!states.empty()) {
            shader.Bind();

            auto &state = states.top();
            state->Run(delta);

            shader.Unbind();
        }

        window.Update();
    }
}

} // namespace veb
