#include "veb/render/RenderSystem.hpp"

#include "veb/component/Components.hpp"
#include "veb/component/ComponentMesh.hpp"
#include "veb/component/ComponentPosition.hpp"
#include "veb/component/ComponentRotation.hpp"
#include "veb/gfx/FragmentShader.hpp"
#include "veb/gfx/VertexShader.hpp"

#include <glm/vec3.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/ext/matrix_transform.hpp>

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

static glm::mat4 CreateEntityMatrix(ComponentPosition &position, ComponentRotation &rotation) {
    glm::mat4 matrix = glm::identity<glm::mat4>();
    matrix = glm::translate(matrix, glm::vec3(position.x, position.y, -position.z));

    // https://en.wikipedia.org/wiki/Aircraft_principal_axes
    matrix = matrix * glm::toMat4(glm::quat(glm::cos(rotation.pitch / 2.f), glm::sin(rotation.pitch / 2.f), 0.f, 0.f));
    matrix = matrix * glm::toMat4(glm::quat(glm::cos(rotation.yaw / 2.f), 0.f, -glm::sin(rotation.yaw / 2.f), 0.f));
    matrix = matrix * glm::toMat4(glm::quat(glm::cos(rotation.roll / 2.f), 0.f, 0.f, glm::sin(rotation.roll / 2.f)));

    return matrix;
}

RenderSystem::RenderSystem() {
    VertexShader vertexShader(vertex_shader_source);
    FragmentShader fragmentShader(fragment_shader_source);

    shader.Attach(vertexShader);
    shader.Attach(fragmentShader);

    shader.Link();

    SetAmbientColor(glm::vec3(1.f, 1.f, 1.f));
    SetLightPosition(glm::vec3(0.f, 100.f, 0.f));
}

void RenderSystem::Render(const Entity &entity) const {
    if (!Components<ComponentMesh>::Has(entity) || !Components<ComponentPosition>::Has(entity) || !Components<ComponentRotation>::Has(entity))
        return;

    shader.Matrix4x4f("model", CreateEntityMatrix(Components<ComponentPosition>::Get(entity), Components<ComponentRotation>::Get(entity)));
    Components<ComponentMesh>::Get(entity).mesh.Render();
}

void RenderSystem::Render(const std::vector<Entity> &entities) const {
    for (const auto &entity : entities)
        Render(entity);
}

} // namespace veb
