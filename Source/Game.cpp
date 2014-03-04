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

    const char* vertSrc =
    "#version 130\n"
    "uniform mat4 in_MvpMatrix;"
    "in vec2 in_Position;"
    "void main() {"
    "   gl_Position = in_MvpMatrix * vec4(in_Position, 0.0, 1.0);"
    "}";

    const char* fragSrc =
    "#version 130\n"
    "out vec4 out_Color;"
    "void main() {"
    "   out_Color = vec4(1.0, 0.0, 0.0, 1.0);"
    "}";

    GLint compileStatus = 0;

    m_VertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(m_VertexShader, 1, &vertSrc, NULL);
    glCompileShader(m_VertexShader);
    glGetShaderiv(m_VertexShader, GL_COMPILE_STATUS, &compileStatus);

    if (compileStatus == GL_FALSE)
        std::cerr << "Error compiling vertex shader" << std::endl;

    m_FragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(m_FragmentShader, 1, &fragSrc, NULL);
    glCompileShader(m_FragmentShader);
    glGetShaderiv(m_FragmentShader, GL_COMPILE_STATUS, &compileStatus);

    if (compileStatus == GL_FALSE)
        std::cerr << "Error compiling fragment shader" << std::endl;

    m_Program = glCreateProgram();
    glAttachShader(m_Program, m_VertexShader);
    glAttachShader(m_Program, m_FragmentShader);
    glLinkProgram(m_Program);

    GLint isLinked = 0;
    glGetProgramiv(m_Program, GL_LINK_STATUS, &isLinked);

    if (isLinked == GL_FALSE)
        std::cerr << "Error linking" << std::endl;

    glUseProgram(m_Program);

    float vertices[] =
    {
        0.f, 0.f, // Bottom left
        m_Width, 0.f, // Bottom right
        m_Width / 2.f, m_Height  // Top center
    };

    glGenBuffers(1, &m_VertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, m_VertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, m_VertexBuffer);
    auto posAttrib = glGetAttribLocation(m_Program, "in_Position");
    glEnableVertexAttribArray(posAttrib);
    glVertexAttribPointer(posAttrib, 2, GL_FLOAT, GL_FALSE, 0, 0);

    auto mvpLocation = glGetUniformLocation(m_Program, "in_MvpMatrix");
    glUniformMatrix4fv(mvpLocation, 1, GL_FALSE, glm::value_ptr(m_MvpMatrix));

    if (glGetError() == GL_NO_ERROR)
        std::cout << "No error" << std::endl;
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

    m_ProjMatrix = glm::mat4
    (
        glm::vec4(2.f / m_Width, 0.f, 0.f, 0.f),
        glm::vec4(0, 2.f / m_Height, 0.f, 0.f),
        glm::vec4(0.f, 0.f, 0.f, 0.f),
        glm::vec4(-1.f, -1.f, 0.f, 1.f)
    );

    m_MvpMatrix = m_ProjMatrix * m_ViewMatrix * m_ModelMatrix;

    auto mvpLocation = glGetUniformLocation(m_Program, "in_MvpMatrix");
    glUniformMatrix4fv(mvpLocation, 1, GL_FALSE, glm::value_ptr(m_MvpMatrix));
}
