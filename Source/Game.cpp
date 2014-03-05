#include "Game.hpp"

#include <iostream>
#include <memory>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Shader.hpp"

Game::Game(int width, int height)
    : m_Width(width)
    , m_Height(height)
{

}

void Game::init()
{
    loadShaders();
    setupMatrices();
}

void Game::loadShaders()
{
    m_ShaderManager.addShader("Simple", std::make_shared<Shader>("Shaders/simple.vert", "Shaders/simple.frag"));
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

void Game::keyEvent(unsigned char key, int x, int y)
{

}

void Game::mouseEvent(int button, int state, int x, int y)
{

}

void Game::specialKeyPressed(int key, int x, int y)
{

}

void Game::specialKeyReleased(int key, int x, int y)
{

}

void Game::update(int delta)
{

}

void Game::display()
{

}

void Game::resize(int width, int height)
{
    m_Width = width;
    m_Height = height;
}
