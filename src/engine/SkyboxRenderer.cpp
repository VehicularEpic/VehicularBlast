#include "veb/engine/SkyboxRenderer.hpp"

#include "veb/gfx/FragmentShader.hpp"
#include "veb/gfx/VertexShader.hpp"

#include <glm/ext/matrix_transform.hpp>

static constexpr const char *vertex_shader_source = R"(
#version 330 core
precision mediump float;

layout(location = 0) in vec2 a_position;

out vec3 np; // Unprojected Near Point
out vec3 fp; // Unprojected Far Point

uniform mat4 projection;
uniform mat4 view;

vec3 unproject(vec2 p, float z) {
    vec4 wp = inverse(view) * inverse(projection) * vec4(p, z, 1.f);
    return wp.xyz / wp.w;
}

void main(void) {
    np = unproject(a_position.xy, 0.f);
    fp = unproject(a_position.xy, 1.f);

    gl_Position = vec4(a_position, 1.f, 1.f);
}
)";

static constexpr const char *fragment_shader_source = R"(
#version 330 core
precision mediump float;

in vec3 np;
in vec3 fp;

layout(location = 0) out vec4 FragColor;

uniform vec3 ambient;

uniform vec3 skyColor;
uniform vec3 groundColor;

void main(void) {
    float t = -np.y / (fp.y - np.y);

    if (t > 0) {
        FragColor = vec4(ambient * groundColor, 1.f);
        return;
    }

    FragColor = vec4(ambient * skyColor, 1.f);
}
)";

namespace veb {

SkyboxRenderer::SkyboxRenderer() {
    VertexShader vertexShader(vertex_shader_source);
    FragmentShader fragmentShader(fragment_shader_source);

    Attach(vertexShader);
    Attach(fragmentShader);

    Link();
}

} // namespace veb
