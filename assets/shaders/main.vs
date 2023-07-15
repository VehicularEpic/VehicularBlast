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
