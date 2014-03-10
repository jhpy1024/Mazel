#ifndef TEST_ENTITY_HPP
#define TEST_ENTITY_HPP

#include "Entity.hpp"

class TestEntity : public Entity
{
public:
    TestEntity(Game* game, glm::vec2 position, glm::vec2 size);

    void setupVertexBuffer() override;
    void setupColorBuffer() override;

    void setupVertexAttrib() override;
    void setupColorAttrib() override;

    void keyPressed(unsigned char key) override;
    void keyReleased(unsigned char key) override;
    void specialKeyPressed(int key) override;
    void specialKeyReleased(int key) override;

    void update(int delta) override;
    void display() override;

private:
    void move(int delta);
    bool moveDelayOver() const;
    void moveUp();
    void moveDown();
    void moveLeft();
    void moveRight();

    void fireIfPossible();
    bool fireDelayOver() const;
    void fireProjectile();

    glm::vec2 getBottomLeft() const;

private:
    bool m_MovingUp;
    bool m_MovingDown;
    bool m_MovingLeft;
    bool m_MovingRight;

    int m_LastTimeMoved;
    const float m_MoveDelay;

    int m_LastTimeFired;
    const float m_FireDelay;
    bool m_Firing;

    const float m_ProjectileRotationOffset;
    const glm::vec2 m_ProjectileSize;
};

#endif // TEST_ENTITY_HPP
