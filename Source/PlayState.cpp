#include "PlayState.hpp"

#include <iostream>

#include <glm/gtc/type_ptr.hpp>

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
    checkCollisions();

}

void PlayState::checkCollisions()
{
    checkIfFinishedLevel();
}

void PlayState::checkIfFinishedLevel()
{
    auto playerPos = m_TestEntity->getPosition();
    auto playerPosCenter = playerPos - (m_TestEntity->getSize() / 2.f);
    auto tilePlayerIsOn = m_Game->getMap().getTileAtPixelPos(playerPosCenter);

    if (tilePlayerIsOn.isFinishTile)
        m_Game->finishedLevel();
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
    enableLighting();
    displayMap();
    disableLighting();
    displayEntities();
}

void PlayState::enableLighting()
{
    m_Game->getShaderManager().useShader("Simple");
    auto lightingEnabledLocation = m_Game->getShaderManager().getShader("Simple")->getUniformLocation("in_LightingEnabled");
    glUniform1i(lightingEnabledLocation, 1);
}

void PlayState::disableLighting()
{
    m_Game->getShaderManager().useShader("Simple");
    auto lightingEnabledLocation = m_Game->getShaderManager().getShader("Simple")->getUniformLocation("in_LightingEnabled");
    glUniform1i(lightingEnabledLocation, 0);
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
