#include "TestEntity.hpp"
#include "Game.hpp"

#include <GL/freeglut.h>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

TestEntity::TestEntity(Game* game, glm::vec2 position, glm::vec2 size)
    : Entity(game, position, size, "TestEntity")
    , m_MovingUp(false)
    , m_MovingDown(false)
    , m_MovingLeft(false)
    , m_MovingRight(false)
    , m_LastTimeMoved(0)
    , m_MoveDelay(50.f)
    , m_Rotation(0.f)
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
    if (glutGet(GLUT_ELAPSED_TIME) - m_LastTimeMoved >= m_MoveDelay)
    {
        if (m_MovingUp)
            m_Position.y += m_Size.y;
        else if (m_MovingDown)
            m_Position.y -= m_Size.y;
        else if (m_MovingLeft)
            m_Position.x -= m_Size.x;
        else if (m_MovingRight)
            m_Position.x += m_Size.x;

        m_LastTimeMoved = glutGet(GLUT_ELAPSED_TIME);
    }
}

void TestEntity::update(int delta)
{
    move(delta);

    m_Rotation += 0.1f;
    if (m_Rotation >= 6.28f)
        m_Rotation = 0.f;
}

void TestEntity::display()
{
    setModelMatrix();
    setupVertexAttrib();
    setupColorAttrib();
    glDrawArrays(GL_TRIANGLES, 0, m_Vertices.size());
}

void TestEntity::setModelMatrix()
{
    m_ModelMatrix = glm::translate(glm::mat4(1.f), glm::vec3(m_Position, 0.f));
    m_ModelMatrix = glm::rotate(m_ModelMatrix, m_Rotation, glm::vec3(0.f, 0.f, 1.f));
    auto mvpMatrix = m_Game->getProjectionMatrix() * m_Game->getViewMatrix() * m_ModelMatrix;

    auto mvpLocation = m_Game->getShaderManager().getShader("Simple")->getUniformLocation("in_MvpMatrix");
    glUniformMatrix4fv(mvpLocation, 1, GL_FALSE, glm::value_ptr(mvpMatrix));
}
