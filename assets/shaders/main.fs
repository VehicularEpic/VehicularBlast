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
