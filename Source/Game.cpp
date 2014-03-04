#include "Game.hpp"

#include <iostream>

#include <GL/gl.h>

Game::Game(int width, int height)
    : m_Width(width)
    , m_Height(height)
{

}

void Game::init()
{

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
