#include "TestEntity.hpp"
#include "Game.hpp"

#include <GL/freeglut.h>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/constants.hpp>

#include <iostream>

TestEntity::TestEntity(Game* game, glm::vec2 position, glm::vec2 size)
    : Entity(game, position, size, "TestEntity")
    , m_MovingUp(false)
    , m_MovingDown(false)
    , m_MovingLeft(false)
    , m_MovingRight(false)
    , m_LastTimeMoved(0)
    , m_MoveDelay(50.f)
{

}

void TestEntity::setupVertices()
{
    m_Vertices =
    {
        -m_Size.x / 2.f, -m_Size.y / 2.f,
        m_Size.x / 2.f, -m_Size.y / 2.f,
        0.f, m_Size.y / 2.f
    };
}

void TestEntity::setupVertexBuffer()
{
    glGenBuffers(1, &m_VertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, m_VertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * m_Vertices.size(), &m_Vertices[0], GL_STATIC_DRAW);
}

void TestEntity::setupVertexAttrib()
{
    glBindBuffer(GL_ARRAY_BUFFER, m_VertexBuffer);
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
}

void TestEntity::setupColorAttrib()
{
    glBindBuffer(GL_ARRAY_BUFFER, m_ColorBuffer);
    auto colorAttrib = m_Game->getShaderManager().getShader("Simple")->getAttribLocation("in_Color");
    glEnableVertexAttribArray(colorAttrib);
    glVertexAttribPointer(colorAttrib, 4, GL_FLOAT, GL_FALSE, 0, 0);
}

void TestEntity::specialKeyPressed(int key)
{
    switch (key)
    {
    case GLUT_KEY_UP:
        m_MovingUp = true;
        break;
    case GLUT_KEY_DOWN:
        m_MovingDown = true;
        break;
    case GLUT_KEY_LEFT:
        m_MovingLeft = true;
        break;
    case GLUT_KEY_RIGHT:
        m_MovingRight = true;
        break;
    default:
        break;
    }
}

void TestEntity::specialKeyReleased(int key)
{
    switch (key)
    {
    case GLUT_KEY_UP:
        m_MovingUp = false;
        break;
    case GLUT_KEY_DOWN:
        m_MovingDown = false;
        break;
    case GLUT_KEY_LEFT:
        m_MovingLeft = false;
        break;
    case GLUT_KEY_RIGHT:
        m_MovingRight = false;
        break;
    default:
        break;
    }
}

void TestEntity::move(int delta)
{
    if (moveDelayOver())
    {
        if (m_MovingUp)
            moveUp();
        else if (m_MovingDown)
            moveDown();
        else if (m_MovingLeft)
            moveLeft();
        else if (m_MovingRight)
            moveRight();

        m_LastTimeMoved = glutGet(GLUT_ELAPSED_TIME);
    }
}

bool TestEntity::moveDelayOver() const
{
    auto currentTime = glutGet(GLUT_ELAPSED_TIME);
    return currentTime - m_LastTimeMoved >= m_MoveDelay;
}

void TestEntity::moveUp()
{
    if (m_Game->getMap().getTileTypeAtPixels(glm::vec2(getBottomLeft().x, getBottomLeft().y + m_Size.y)) == 0)
        return;
    m_Position.y += m_Size.y;
    m_Rotation = 0.f;
}

void TestEntity::moveDown()
{
    if (m_Game->getMap().getTileTypeAtPixels(glm::vec2(getBottomLeft().x, getBottomLeft().y - m_Size.y)) == 0)
        return;
    m_Position.y -= m_Size.y;
    m_Rotation = 180.f;
}

void TestEntity::moveLeft()
{
    if (m_Game->getMap().getTileTypeAtPixels(glm::vec2(getBottomLeft().x - m_Size.x, getBottomLeft().y)) == 0)
        return;
    m_Position.x -= m_Size.x;
    m_Rotation = 90.f;
}

void TestEntity::moveRight()
{
    if (m_Game->getMap().getTileTypeAtPixels(glm::vec2(getBottomLeft().x + m_Size.x, getBottomLeft().y)) == 0)
        return;
    m_Position.x += m_Size.x;
    m_Rotation = 270.f;
}

glm::vec2 TestEntity::getBottomLeft() const
{
    return m_Position - (m_Size / 2.f);
}

void TestEntity::update(int delta)
{
    move(delta);
}

void TestEntity::display()
{
    updateMatrices();
    setupVertexAttrib();
    setupColorAttrib();
    glDrawArrays(GL_TRIANGLES, 0, m_Vertices.size());
}
