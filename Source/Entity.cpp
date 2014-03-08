#include "Entity.hpp"

#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Game.hpp"

Entity::Entity(Game* game, glm::vec2 position, glm::vec2 size, const std::string& id)
    : m_Game(game)
    , m_Position(position)
    , m_Size(size)
    , m_ID(id)
    , m_Scale(1.f, 1.f)
    , m_Rotation(0.f)
{

}

Entity::~Entity()
{
    glDeleteBuffers(1, &m_VertexBuffer);
    glDeleteBuffers(1, &m_ColorBuffer);
}

void Entity::init()
{
    setupVertices();
    setupVertexBuffer();
    setupVertexAttrib();

    setupColors();
    setupColorBuffer();
    setupColorAttrib();
}

void Entity::updateMatrices()
{
    m_TranslationMatrix = glm::translate(glm::mat4(1.f), glm::vec3(m_Position, 0.f));
    m_RotationMatrix = glm::rotate(glm::mat4(1.f), m_Rotation, glm::vec3(0.f, 0.f, 0.1f));
    m_ScaleMatrix = glm::scale(glm::mat4(1.f), glm::vec3(m_Scale, 0.f));

    m_ModelMatrix = m_TranslationMatrix * m_RotationMatrix * m_ScaleMatrix;

    passMatrixToShader();
}

void Entity::passMatrixToShader()
{
    auto projectionMatrix = m_Game->getProjectionMatrix();
    auto viewMatrix = m_Game->getViewMatrix();

    auto mvpMatrix = projectionMatrix * viewMatrix * m_ModelMatrix;
    auto mvpLocation = m_Game->getShaderManager().getShader("Simple")->getUniformLocation("in_MvpMatrix");
    glUniformMatrix4fv(mvpLocation, 1, GL_FALSE, glm::value_ptr(mvpMatrix));
}

void Entity::keyEvent(unsigned char key)
{
}

void Entity::specialKeyPressed(int key)
{
}

void Entity::specialKeyReleased(int key)
{
}

void Entity::update(int delta)
{
}

void Entity::setPosition(glm::vec2 position)
{
    m_Position = position;
}

void Entity::setSize(glm::vec2 size)
{
    m_Size = size;
}

glm::vec2 Entity::getPosition() const
{
    return m_Position;
}

glm::vec2 Entity::getSize() const
{
    return m_Size;
}

std::string Entity::getID() const
{
    return m_ID;
}
