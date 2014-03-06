#include "Entity.hpp"

Entity::Entity(Game* game, glm::vec2 position, glm::vec2 size, const std::string& id)
    : m_Game(game)
    , m_Position(position)
    , m_Size(size)
    , m_ID(id)
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

    setupColors();
    setupColorBuffer();
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
