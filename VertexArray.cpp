//
// Created by marco on 1/7/19.
//

#include "VertexArray.h"

VertexArray::VertexArray(const float *verts, unsigned int numVerts, const unsigned int *indices,
                         unsigned int numIndices) {
    // Create VAO and store ID
    glGenVertexArrays(1, &mVertexArray);
    glBindVertexArray(mVertexArray);

    // Create a vertex buffer
    glGenBuffers(1, &mVertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, mVertexBuffer);

    glBufferData(
            GL_ARRAY_BUFFER,    // The active buffer type to write to
            numVerts*3* sizeof(float),  // Number of bytes to copy
            verts,                      // Source to copy from (pointer)
            GL_STATIC_DRAW              // How will we use this data
            );

    // Next create the index buffer
    glGenBuffers(1, &mIndexBuffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mIndexBuffer);

    // Copy indices data into index buffer
    glBufferData(
            GL_ELEMENT_ARRAY_BUFFER,        // Index buffer
            numIndices * sizeof(unsigned int), // Size of data
            indices,
            GL_STATIC_DRAW
            );

    // Specify the vertex attributes
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(
            0,      // Attribute index (0 for first one)
            3,      // Number of components (3 in this case)
            GL_FLOAT,// Type of components
            GL_FALSE, // (only used for integral types)
            sizeof(float) * 3,
            nullptr
            );
}

VertexArray::~VertexArray() {
    glDeleteBuffers(1, &mVertexBuffer);
    glDeleteBuffers(1, &mIndexBuffer);
    glDeleteVertexArrays(1, &mVertexArray);
}

void VertexArray::SetActive() {
    glBindVertexArray(mVertexArray);
}