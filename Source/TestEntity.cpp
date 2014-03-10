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
    , m_LastTimeFired(0)
    , m_FireDelay(200.f)
    , m_ProjectileRotationOffset(20.f)
    , m_ProjectileSize(15.f)
    , m_Firing(false)
{

}

void TestEntity::setupVertexBuffer()
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

void TestEntity::setupVertexAttrib()
{
    m_VertexBuffer.bind();
    auto posAttrib = m_Game->getShaderManager().getShader("Simple")->getAttribLocation("in_Position");
    glEnableVertexAttribArray(posAttrib);
    glVertexAttribPointer(posAttrib, 2, GL_FLOAT, GL_FALSE, 0, 0);
}

void TestEntity::setupColorBuffer()
{
    m_ColorBuffer.init();
    m_ColorBuffer.bind();
    m_ColorBuffer.setData(
        {
            1.f, 0.f, 0.f, 1.f,
            0.f, 1.f, 0.f, 1.f,
            0.f, 0.f, 1.f, 1.f
        });
}

void TestEntity::setupColorAttrib()
{
    m_ColorBuffer.bind();
    auto colorAttrib = m_Game->getShaderManager().getShader("Simple")->getAttribLocation("in_Color");
    glEnableVertexAttribArray(colorAttrib);
    glVertexAttribPointer(colorAttrib, 4, GL_FLOAT, GL_FALSE, 0, 0);
}

void TestEntity::keyPressed(unsigned char key)
{
    switch (key)
    {
    case ' ':
        m_Firing = true;
        break;
    default:
        break;
    }
}

void TestEntity::keyReleased(unsigned char key)
{
    switch (key)
    {
    case ' ':
        m_Firing = false;
        break;
    default:
        break;
    }
}

void TestEntity::fireIfPossible()
{
    if (shootDelayOver())
    {
        shootProjectile();
    }
}

bool TestEntity::fireDelayOver() const
{
    auto currentTime = glutGet(GLUT_ELAPSED_TIME);
    return currentTime - m_LastTimeFired >= m_FireDelay;
}

void TestEntity::fireProjectile()
{
    auto forwardProjectileRotation = glm::radians<float>(-m_Rotation);
    auto leftProjectileRotation = glm::radians<float>(-m_Rotation - m_ProjectileRotationOffset);
    auto rightProjectileRotation = glm::radians<float>(-m_Rotation + m_ProjectileRotationOffset);

    m_Game->createProjectile(m_Position, m_ProjectileSize, forwardProjectileRotation);
    m_Game->createProjectile(m_Position, m_ProjectileSize, leftProjectileRotation);
    m_Game->createProjectile(m_Position, m_ProjectileSize, rightProjectileRotation);

    m_LastTimeFired = glutGet(GLUT_ELAPSED_TIME);
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
    auto tileAbovePos = glm::vec2(getBottomLeft().x, getBottomLeft().y + m_Size.y);
    auto tileAbove = m_Game->getMap().getTileAtPixelPos(tileAbovePos);

    if (!tileAbove.isCollidable)
    {
        m_Position.y += m_Size.y;
        m_Rotation = 0.f;
    }
}

void TestEntity::moveDown()
{
    auto tileBelowPos = glm::vec2(getBottomLeft().x, getBottomLeft().y - m_Size.y);
    auto tileBelow = m_Game->getMap().getTileAtPixelPos(tileBelowPos);

    if (!tileBelow.isCollidable)
    {
        m_Position.y -= m_Size.y;
        m_Rotation = 180.f;
    }
}

void TestEntity::moveLeft()
{
    auto tileLeftPos = glm::vec2(getBottomLeft().x - m_Size.x, getBottomLeft().y);
    auto tileLeft = m_Game->getMap().getTileAtPixelPos(tileLeftPos);

    if (!tileLeft.isCollidable)
    {
        m_Position.x -= m_Size.x;
        m_Rotation = 90.f;
    }
}

void TestEntity::moveRight()
{
    auto tileRightPos = glm::vec2(getBottomLeft().x + m_Size.x, getBottomLeft().y);
    auto tileRight = m_Game->getMap().getTileAtPixelPos(tileRightPos);

    if (!tileRight.isCollidable)
    {
        m_Position.x += m_Size.x;
        m_Rotation = 270.f;
    }
}

glm::vec2 TestEntity::getBottomLeft() const
{
    return m_Position - (m_Size / 2.f);
}

void TestEntity::update(int delta)
{
    move(delta);

    if (m_Firing)
        fireIfPossible();
}

void TestEntity::display()
{
    updateMatrices();
    setupVertexAttrib();
    setupColorAttrib();
    glDrawArrays(GL_TRIANGLES, 0, m_VertexBuffer.getDataSize());
}
