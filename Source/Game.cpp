#include "Game.hpp"

#include <iostream>

#include <glm/gtc/matrix_transform.hpp>

Game::Game(int width, int height)
    : m_Width(width)
    , m_Height(height)
{

}

void Game::setupGL()
{
    m_ProjMatrix = glm::ortho(0, m_Width, 0, m_Height);
    m_MvpMatrix = m_ProjMatrix * m_ViewMatrix * m_ModelMatrix;

    createShaders();
}

void Game::createShaders()
{
    m_ShaderManager.addShader("Sprite", std::make_shared<Shader>("Shaders/sprite.vert", "Shaders/sprite.frag"));
}

void Game::keyPressed(unsigned char key, int x, int y)
{

}

void Game::specialKeyPressed(int key, int x, int y)
{

}

void Game::specialKeyReleased(int key, int x, int y)
{

}

void Game::mousePressed(int button, int state, int x, int y)
{

}

void Game::update(int delta)
{

}

void Game::render()
{

}
