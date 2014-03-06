#include "Entity.hpp"

Entity::Entity(Game* game, glm::vec2 position, glm::vec2 size)
    : m_Game(game)
    , m_Position(position)
    , m_Size(size)
{

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
