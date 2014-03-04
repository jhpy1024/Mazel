#include "Game.hpp"

#include <iostream>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

Game::Game(int width, int height)
    : m_Width(width)
    , m_Height(height)

{

}

void Game::init()
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

    m_Shader = std::unique_ptr<Shader>(new Shader("Shaders/simple.vert", "Shaders/simple.frag"));
    m_Shader->use();

    float vertices[] =
    {
        0.f, 0.f, // Bottom left
        m_Width, 0.f, // Bottom right
        m_Width / 2.f, m_Height  // Top center
    };

    glGenBuffers(1, &m_VertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, m_VertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    float colors[] =
    {
        1.f, 0.f, 0.f, 1.f,
        0.f, 1.f, 0.f, 1.f,
        0.f, 0.f, 1.f, 1.f
    };

    glGenBuffers(1, &m_ColorBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, m_ColorBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(colors), colors, GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, m_VertexBuffer);
    auto posAttrib = m_Shader->getAttribLocation("in_Position");
    glEnableVertexAttribArray(posAttrib);
    glVertexAttribPointer(posAttrib, 2, GL_FLOAT, GL_FALSE, 0, 0);

    glBindBuffer(GL_ARRAY_BUFFER, m_ColorBuffer);
    auto colorAttrib = m_Shader->getAttribLocation("in_Color");
    glEnableVertexAttribArray(colorAttrib);
    glVertexAttribPointer(colorAttrib, 4, GL_FLOAT, GL_FALSE, 0, 0);

    auto mvpLocation = m_Shader->getUniformLocation("in_MvpMatrix");
    glUniformMatrix4fv(mvpLocation, 1, GL_FALSE, glm::value_ptr(m_MvpMatrix));
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
    glDrawArrays(GL_TRIANGLES, 0, 3);
}

void Game::resize(int width, int height)
{
    m_Width = width;
    m_Height = height;
}
