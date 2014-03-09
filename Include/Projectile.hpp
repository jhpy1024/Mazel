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

    bool isAlive() const;

private:
    int m_TimeCreated;
    const int m_Lifetime;
    bool m_IsAlive;

    glm::vec2 m_Velocity;
    const float m_Speed;
};

#endif // PROJECTILE_HPP
