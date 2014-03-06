#ifndef TEST_ENTITY_HPP
#define TEST_ENTITY_HPP

#include "Entity.hpp"

class TestEntity : public Entity
{
public:
    TestEntity(Game* game, glm::vec2 position, glm::vec2 size);

    void setupVertices() override;
    void setupColors() override;

    void setupVertexBuffer() override;
    void setupColorBuffer() override;

    void update(int delta) override;
    void display() override;

    void move(glm::vec2 direction);

private:
    const float m_Speed;
};

#endif // TEST_ENTITY_HPP
