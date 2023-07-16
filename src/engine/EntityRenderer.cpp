#include "veb/engine/EntityRenderer.hpp"

#include "veb/gfx/FragmentShader.hpp"
#include "veb/gfx/VertexShader.hpp"

static constexpr const char *vertex_shader_source = R"(
#version 330 core
precision mediump float;

layout(location = 0) in vec3 a_position;
layout(location = 1) in vec3 a_normals;
layout(location = 2) in vec4 a_colors;

out vec3 v_colors;
out vec3 v_normals;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;

void main(void) {
    vec4 position = vec4(a_position, 1.);

    v_colors = a_colors.rgb;
    v_normals = normalize(mat3(transpose(inverse(model))) * a_normals);

    gl_Position = projection * view * model * position;
}
)";

static constexpr const char *fragment_shader_source = R"(
#version 330 core
precision mediump float;

in vec3 v_colors;
in vec3 v_normals;

layout(location = 0) out vec4 frag_color;

uniform vec3 ambient;
uniform vec3 u_LightPos;

void main(void) {
    vec3 ambient_factor = 0.1 * ambient;

    vec3 n = normalize(v_normals);
    vec3 l_dir = normalize(u_LightPos.xyz);
    float diff = max(dot(n, l_dir), 0.0);

    vec3 diffuse_factor = diff * ambient;
    frag_color = vec4((ambient_factor + diffuse_factor) * v_colors, 1.);
}
)";

namespace veb {

EntityRenderer::EntityRenderer() {
    VertexShader vertexShader(vertex_shader_source);
    FragmentShader fragmentShader(fragment_shader_source);

    shader.Attach(vertexShader);
    shader.Attach(fragmentShader);

    shader.Link();
}

EntityRenderer::EntityRenderer(EntityRenderer &&e) noexcept
    : shader(std::move(e.shader)) {
}

} // namespace veb
