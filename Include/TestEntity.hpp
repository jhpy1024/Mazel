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

    void keyEvent(unsigned char key) override;
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

    void shootIfPossible();
    bool shootDelayOver() const;
    void shootProjectile();

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

    float m_ProjectileRotationOffset;
};

#endif // TEST_ENTITY_HPP
