#include "Buffer.hpp"

Buffer::Buffer()
{
    glGenBuffers(1, &m_Buffer);
}

void Buffer::bind()
{
    glBindBuffer(GL_ARRAY_BUFFER, m_Buffer);
}

void Buffer::setData(const std::vector<float>& data)
{
    bind();

    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * data.size(), &data[0], GL_STATIC_DRAW);
}
