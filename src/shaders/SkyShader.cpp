#include "veb/shaders/SkyShader.hpp"

#include "veb/gfx/FragmentShader.hpp"
#include "veb/gfx/VertexShader.hpp"

#define VERTEX_SHADER_SOURCE R""(
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
)""

#define FRAGMENT_SHADER_SOURCE R""(
#version 330 core
precision mediump float;

in vec3 np;
in vec3 fp;

layout(location = 0) out vec4 FragColor;

uniform vec3 ambient;

uniform vec3 skyColor;
uniform vec3 groundColor;
uniform vec3 fadeColor = vec3(1.f);

vec3 gradient(vec3 color, float y, float edge) {  
    return mix(color, fadeColor, smoothstep(0.f, edge, y));
}

void main(void) {
    float t = -np.y / (fp.y - np.y);

    if (t > 0) {
        FragColor = vec4(gradient(ambient * groundColor, t, 0.4f), 1.f);
        return;
    }

    FragColor = vec4(gradient(ambient * skyColor, t, -0.08f), 1.f);
}
)""

namespace veb {

SkyShader::SkyShader() {
    Attach(VertexShader(VERTEX_SHADER_SOURCE));
    Attach(FragmentShader(FRAGMENT_SHADER_SOURCE));
    Link();
}

} // namespace veb
