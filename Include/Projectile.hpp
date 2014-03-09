#ifndef PROJECTILE_HPP
#define PROJECTILE_HPP

#include <glm/glm.hpp>

#include "Entity.hpp"

class Projectile : public Entity
{
public:
    Projectile(Game* game, glm::vec2 position, glm::vec2 size, float angle);

    void setupVertexBuffer() override;
    void setupColorBuffer() override;

    void setupVertexAttrib() override;
    void setupColorAttrib() override;

    void update(int delta) override;
    void display() override;

private:
    int m_TimeCreated;
    const int m_Lifetime;

    glm::vec2 m_Velocity;
};

#endif // PROJECTILE_HPP
