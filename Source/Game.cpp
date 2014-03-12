#include "Game.hpp"

#include <iostream>
#include <memory>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Shader.hpp"
#include "PlayState.hpp"
#include "MenuState.hpp"

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

    m_CurrentState = std::make_shared<PlayState>(this);
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
    m_ShaderManager.addShader("Texture", std::make_shared<Shader>("Shaders/texture.vert", "Shaders/texture.frag"));
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
}

void Game::keyPressed(unsigned char key, int x, int y)
{
    m_CurrentState->keyPressed(key, x, y);
}

void Game::keyReleased(unsigned char key, int x, int y)
{
    m_CurrentState->keyReleased(key, x, y);
}

void Game::mouseEvent(int button, int state, int x, int y)
{
    m_CurrentState->mouseEvent(button, state, x, y);
}

void Game::specialKeyPressed(int key, int x, int y)
{
    m_CurrentState->specialKeyPressed(key, x, y);
}

void Game::specialKeyReleased(int key, int x, int y)
{
    m_CurrentState->specialKeyReleased(key, x, y);
}

void Game::update(int delta)
{
    addNewEntities();

    m_CurrentState->update(delta);
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
    m_CurrentState->display();
}

void Game::resize(int width, int height)
{
    m_Width = width;
    m_Height = height;
}

std::shared_ptr<TestEntity>& Game::getPlayer()
{
    return m_TestEntity;
}

std::vector<std::shared_ptr<Entity>>& Game::getEntities()
{
    return m_Entities;
}

std::vector<std::shared_ptr<Projectile>>& Game::getProjectiles()
{
    return m_Projectiles;
}

glm::mat4 Game::getProjectionMatrix() const
{
    return m_ProjMatrix;
}

glm::mat4 Game::getViewMatrix() const
{
    return m_ViewMatrix;
}

Map& Game::getMap()
{
    return m_TestMap;
}

ShaderManager& Game::getShaderManager()
{
    return m_ShaderManager;
}
