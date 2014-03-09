#include "Projectile.hpp"

#include <GL/freeglut.h>

Projectile::Projectile(Game* game, glm::vec2 position, glm::vec2 size, float angle)
    : Entity(game, position, size, "Projectile")
    , m_TimeCreated(glutGet(GLUT_ELAPSED_TIME))
    , m_Lifetime(5000)
{

}

void Projectile::setupVertexBuffer()
{

}

void Projectile::setupColorBuffer()
{

}

void Projectile::setupVertexAttrib()
{

}

void Projectile::setupColorAttrib()
{

}

void Projectile::update(int delta)
{

}

void Projectile::display()
{

}
