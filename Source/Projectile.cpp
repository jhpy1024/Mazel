#include "Projectile.hpp"

#include <GL/freeglut.h>

#include "Game.hpp"

Projectile::Projectile(Game* game, glm::vec2 position, glm::vec2 size, float angle)
    : Entity(game, position, size, "Projectile")
    , m_TimeCreated(glutGet(GLUT_ELAPSED_TIME))
    , m_Lifetime(5000)
    , m_Speed(0.8f)
{
    m_Velocity = glm::vec2(m_Speed * std::sin(angle), m_Speed * std::cos(angle));
    m_Rotation = -((angle * 180.f) / 3.14f);
}

void Projectile::setupVertexBuffer()
{
    m_VertexBuffer.init();
    m_VertexBuffer.bind();
    m_VertexBuffer.setData(
        {
            -m_Size.x / 2.f, -m_Size.y / 2.f,
            m_Size.x / 2.f, -m_Size.y / 2.f,
            0.f, m_Size.y / 2.f
        });
}

void Projectile::setupColorBuffer()
{
    m_ColorBuffer.init();
    m_ColorBuffer.bind();
    m_ColorBuffer.setData(
        {
            0.f, 1.f, 1.f, 1.f,
            0.f, 1.f, 1.f, 1.f,
            0.f, 1.f, 1.f, 1.f
        });
}

void Projectile::setupVertexAttrib()
{
    m_VertexBuffer.bind();
    auto posAttrib = m_Game->getShaderManager().getShader("Simple")->getAttribLocation("in_Position");
    glEnableVertexAttribArray(posAttrib);
    glVertexAttribPointer(posAttrib, 2, GL_FLOAT, GL_FALSE, 0, 0);
}

void Projectile::setupColorAttrib()
{
    m_ColorBuffer.bind();
    auto colorAttrib = m_Game->getShaderManager().getShader("Simple")->getAttribLocation("in_Color");
    glEnableVertexAttribArray(colorAttrib);
    glVertexAttribPointer(colorAttrib, 4, GL_FLOAT, GL_FALSE, 0, 0);
}

void Projectile::update(int delta)
{
    m_Position += m_Velocity * static_cast<float>(delta);
}

void Projectile::display()
{
    updateMatrices();
    setupVertexAttrib();
    setupColorAttrib();
    glDrawArrays(GL_TRIANGLES, 0, m_VertexBuffer.getDataSize());
}
