#include "veb/gfx/Mesh.hpp"

#include <glad/gl.h>

static constexpr uint8_t PositionIndex = 0;
static constexpr uint8_t PositionElementCount = 3;
static constexpr uint8_t PositionOffset = 0;

static constexpr uint8_t NormalIndex = 1;
static constexpr uint8_t NormalElementCount = 3;
static constexpr uint8_t NormalOffset = sizeof(float) * PositionElementCount;

static constexpr uint8_t ColorIndex = 2;
static constexpr uint8_t ColorElementCount = 4;
static constexpr uint8_t ColorOffset = sizeof(float) * (PositionElementCount + NormalElementCount);

static constexpr uint8_t Stride = (PositionElementCount + NormalElementCount + ColorElementCount) * sizeof(float);

namespace veb {

Mesh::Mesh(std::vector<float> data, uint32_t count) : count(count) {
    if (data.empty())
        return;

    glGenVertexArrays(1, &object);
    glBindVertexArray(object);

    GLuint buffer;
    glGenBuffers(1, &buffer);
    glBindBuffer(GL_ARRAY_BUFFER, buffer);
    glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(GLfloat), &data[0], GL_STATIC_DRAW);

    glEnableVertexAttribArray(PositionIndex);
    glVertexAttribPointer(PositionIndex, PositionElementCount,
            GL_FLOAT, GL_FALSE, Stride, PositionOffset);

    glEnableVertexAttribArray(NormalIndex);
    glVertexAttribPointer(NormalIndex, NormalElementCount,
            GL_FLOAT, GL_FALSE, Stride, reinterpret_cast<void *>(NormalOffset));

    glEnableVertexAttribArray(ColorIndex);
    glVertexAttribPointer(ColorIndex, ColorElementCount,
            GL_FLOAT, GL_FALSE, Stride, reinterpret_cast<void *>(ColorOffset));

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    glDeleteBuffers(1, &buffer);
}

Mesh::~Mesh() {
    glDeleteVertexArrays(1, &object);
}

Mesh::Mesh(Mesh &&mesh) noexcept
    : object(mesh.object), count(mesh.count) {
    mesh.object = 0;
    mesh.count = 0;
}

void Mesh::Render() const {
    glBindVertexArray(object);
    glDrawArrays(GL_TRIANGLES, 0, count);
    glBindVertexArray(0);
}

} // namespace veb
