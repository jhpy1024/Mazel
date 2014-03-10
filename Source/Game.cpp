#include "Game.hpp"

#include <iostream>
#include <memory>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Shader.hpp"

Game::Game(int width, int height)
    : m_Width(width)
    , m_Height(height)
    , m_TestMap("Maps/testMap.txt", this)
{

}

void Game::init()
{
    loadShaders();
    setupMatrices();

    m_TestMap.init();

    createTestEntity(glm::vec2(32.f * 1.5f), glm::vec2(32.f));
}

void Game::createTestEntity(glm::vec2 position, glm::vec2 size)
{
    auto testEntity = std::make_shared<TestEntity>(this, position, size);

    testEntity->init();
    m_EntitiesToAdd.push_back(testEntity);
    m_TestEntity = testEntity;
}

void Game::createProjectile(glm::vec2 position, glm::vec2 size, float angle)
{
    auto projectile = std::make_shared<Projectile>(this, position, size, angle);

    projectile->init();
    m_EntitiesToAdd.push_back(projectile);
    m_Projectiles.push_back(projectile);
}

void Game::loadShaders()
{
    m_ShaderManager.addShader("Simple", std::make_shared<Shader>("Shaders/simple.vert", "Shaders/simple.frag"));
    m_ShaderManager.useShader("Simple");
}

void Game::setupMatrices()
{
    m_ProjMatrix = glm::mat4
    (
        glm::vec4(2.f / m_Width, 0.f, 0.f, 0.f),
        glm::vec4(0, 2.f / m_Height, 0.f, 0.f),
        glm::vec4(0.f, 0.f, 0.f, 0.f),
        glm::vec4(-1.f, -1.f, 0.f, 1.f)
    );
    m_ViewMatrix = glm::mat4(1.f);
    m_ModelMatrix = glm::mat4(1.f);
    m_MvpMatrix = m_ProjMatrix * m_ViewMatrix * m_ModelMatrix;

    auto mvpLocation = m_ShaderManager.getShader("Simple")->getUniformLocation("in_MvpMatrix");
    glUniformMatrix4fv(mvpLocation, 1, GL_FALSE, glm::value_ptr(m_MvpMatrix));
}

void Game::keyPressed(unsigned char key, int x, int y)
{
    for (auto entity : m_Entities)
    {
        entity->keyPressed(key);
    }
}

void Game::keyReleased(unsigned char key, int x, int y)
{
    for (auto entity : m_Entities)
    {
        entity->keyReleased(key);
    }
}

void Game::mouseEvent(int button, int state, int x, int y)
{

}

void Game::specialKeyPressed(int key, int x, int y)
{
    for (auto entity : m_Entities)
    {
        entity->specialKeyPressed(key);
    }
}

void Game::specialKeyReleased(int key, int x, int y)
{
    for (auto entity : m_Entities)
    {
        entity->specialKeyReleased(key);
    }
}

void Game::update(int delta)
{
    updateEntities(delta);
    addNewEntities();
}

void Game::updateEntities(int delta)
{
    for (auto entity : m_Entities)
    {
        entity->update(delta);
    }
}

void Game::addNewEntities()
{
    for (auto newEntity : m_EntitiesToAdd)
    {
        m_Entities.push_back(newEntity);
    }

    m_EntitiesToAdd.clear();
}

void Game::display()
{
    m_TestMap.display();

    for (auto entity : m_Entities)
    {
        entity->display();
    }
}

void Game::resize(int width, int height)
{
    m_Width = width;
    m_Height = height;
}

glm::mat4 Game::getProjectionMatrix() const
{
    return m_ProjMatrix;
}

glm::mat4 Game::getViewMatrix() const
{
    return m_ViewMatrix;
}

const Map& Game::getMap() const
{
    return m_TestMap;
}

ShaderManager& Game::getShaderManager()
{
    return m_ShaderManager;
}
