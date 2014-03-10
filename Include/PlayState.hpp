#ifndef PLAY_STATE_HPP
#define PLAY_STATE_HPP

#include "GameState.hpp"

#include <vector>
#include <memory>

#include "TestEntity.hpp"
#include "Projectile.hpp"
#include "Entity.hpp"
#include "Map.hpp"

class PlayState : public GameState
{
public:
    PlayState(Game* game);

    void keyPressed(unsigned char key, int x, int y) override;
    void keyReleased(unsigned char key, int x, int y) override;
    void specialKeyPressed(int key, int x, int y) override;
    void specialKeyReleased(int key, int x, int y) override;

    void update(int delta) override;
    void display() override;

private:
    void updateEntities(int delta);

    void displayMap();
    void displayEntities();

private:
    std::shared_ptr<TestEntity>& m_TestEntity;
    std::vector<std::shared_ptr<Entity>>& m_Entities;
    std::vector<std::shared_ptr<Projectile>>& m_Projectiles;

    Map& m_TestMap;
};

#endif // PLAY_STATE_HPP
