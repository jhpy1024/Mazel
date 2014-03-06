#include "TestEntity.hpp"
#include "Game.hpp"

TestEntity::TestEntity(Game* game, glm::vec2 position, glm::vec2 size)
    : Entity(game, position, size, "TestEntity")
    , m_Speed(5.f)
{

}

void TestEntity::setupVertices()
{
    m_Vertices =
    {
        0.f, 0.f,
        m_Size.x, 0.f,
        m_Size.x / 2.f, m_Size.y
    };
}

void TestEntity::setupVertexBuffer()
{
    glGenBuffers(1, &m_VertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, m_VertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * m_Vertices.size(), &m_Vertices[0], GL_STATIC_DRAW);

    auto posAttrib = m_Game->getShaderManager().getShader("Simple")->getAttribLocation("in_Position");
    glEnableVertexAttribArray(posAttrib);
    glVertexAttribPointer(posAttrib, 2, GL_FLOAT, GL_FALSE, 0, 0);
}

void TestEntity::setupColors()
{
    m_Colors =
    {
        1.f, 0.f, 0.f, 1.f,
        0.f, 1.f, 0.f, 1.f,
        0.f, 0.f, 1.f, 1.f
    };
}

void TestEntity::setupColorBuffer()
{
    glGenBuffers(1, &m_ColorBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, m_ColorBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * m_Colors.size(), &m_Colors[0], GL_STATIC_DRAW);

    auto colorAttrib = m_Game->getShaderManager().getShader("Simple")->getAttribLocation("in_Color");
    glEnableVertexAttribArray(colorAttrib);
    glVertexAttribPointer(colorAttrib, 4, GL_FLOAT, GL_FALSE, 0, 0);
}

void TestEntity::update(int delta)
{
    auto offsetLocation = m_Game->getShaderManager().getShader("Simple")->getUniformLocation("in_Offset");
    glUniform2f(offsetLocation, m_Position.x, m_Position.y);
}

void TestEntity::display()
{
    glDrawArrays(GL_TRIANGLES, 0, m_Vertices.size());
}
