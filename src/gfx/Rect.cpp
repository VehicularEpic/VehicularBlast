#include "veb/gfx/Rect.hpp"

#include <glad/gl.h>

namespace veb {

Rect::Rect() {
    GLbyte verts[8] = {
            -1, -1, // Top Left
            1, -1,  // Top Right
            1, 1,   // Bottom Right
            -1, 1,  // Bottom Left
    };

    GLubyte elements[6] = {
            0, 1, 2, // Top Left + Top Right + Bottom Right
            2, 3, 0, // Bottom Right + Bottom Left + Top Left
    };

    glCreateVertexArrays(1, &object);
    glBindVertexArray(object);

    GLuint buffers[2];
    glGenBuffers(2, &buffers[0]);

    glBindBuffer(GL_ARRAY_BUFFER, buffers[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(verts), &verts[0], GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_BYTE, GL_FALSE, 2, 0);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffers[1]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(elements), &elements[0], GL_STATIC_DRAW);

    glBindVertexArray(0);
    glDeleteBuffers(2, &buffers[0]);
}

Rect::~Rect() {
    glDeleteVertexArrays(1, &object);
}

void Rect::Render() const {
    glBindVertexArray(object);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_BYTE, 0);
    glBindVertexArray(0);
}

const Rect &Rect::GetInstance() {
    static Rect rect;
    return rect;
}

} // namespace veb
