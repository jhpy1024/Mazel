#include "PlayState.hpp"

#include <iostream>

#include "Game.hpp"

PlayState::PlayState(Game* game)
    : GameState(game)
    , m_TestEntity(game->getPlayer())
    , m_Entities(game->getEntities())
    , m_Projectiles(game->getProjectiles())
    , m_TestMap(game->getMap())
{

}

void PlayState::keyPressed(unsigned char key, int x, int y)
{
    for (auto entity : m_Entities)
    {
        entity->keyPressed(key);
    }
}

void PlayState::keyReleased(unsigned char key, int x, int y)
{
    for (auto entity : m_Entities)
    {
        entity->keyReleased(key);
    }
}

void PlayState::specialKeyPressed(int key, int x, int y)
{
    for (auto entity : m_Entities)
    {
        entity->specialKeyPressed(key);
    }
}

void PlayState::specialKeyReleased(int key, int x, int y)
{
    for (auto entity : m_Entities)
    {
        entity->specialKeyReleased(key);
    }
}

void PlayState::update(int delta)
{
    updateEntities(delta);
}

void PlayState::updateEntities(int delta)
{
    for (auto entity : m_Entities)
    {
        entity->update(delta);
    }
}

void PlayState::display()
{
    displayMap();
    displayEntities();
}

void PlayState::displayMap()
{
    m_TestMap.display();
}

void PlayState::displayEntities()
{
    for (auto entity : m_Entities)
    {
        entity->display();
    }
}
