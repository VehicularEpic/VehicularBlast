#version 330 core
precision mediump float;

in vec3 v_colors;
in vec3 v_normals;

layout(location = 0) out vec4 frag_color;

uniform vec3 u_LightPos;

void main(void) {
    vec3 n = normalize(v_normals);
    vec3 l_dir = normalize(u_LightPos.xyz);
    float intensity = clamp(dot(n, l_dir), 0., 1.);

    vec3 diffuse = vec3(.01) + intensity;
    frag_color = vec4(diffuse * v_colors, 1.);
}
