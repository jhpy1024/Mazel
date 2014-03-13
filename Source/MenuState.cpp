#include "MenuState.hpp"

#include <SOIL.h>

#include <iostream>

#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Game.hpp"
#include "PlayState.hpp"

MenuState::MenuState(Game* game)
    : GameState(game)
    , m_TextureFileName("Textures/menuScreen.png")
{
    m_Game->getShaderManager().useShader("Texture");

    createTexture();
    createVertexBuffer();
    setupVertexAttrib();

    passTextureToShader();
    passMatrixToShader();
}

MenuState::~MenuState()
{
    glDeleteTextures(1, &m_Texture);
}

void MenuState::passMatrixToShader()
{
    auto mvpLocation = m_Game->getShaderManager().getShader("Texture")->getUniformLocation("in_MvpMatrix");
    glUniformMatrix4fv(mvpLocation, 1, GL_FALSE, glm::value_ptr(glm::mat4(1.f)));
}

void MenuState::passTextureToShader()
{
    auto texLocation = m_Game->getShaderManager().getShader("Texture")->getUniformLocation("in_Texture");
    glUniform1i(texLocation, GL_TEXTURE0);
}

void MenuState::setupVertexAttrib()
{
    auto posAttrib = m_Game->getShaderManager().getShader("Texture")->getAttribLocation("in_Position");
    auto texCoordAttrib = m_Game->getShaderManager().getShader("Texture")->getAttribLocation("in_TexCoord");

    glVertexAttribPointer(posAttrib, 2, GL_FLOAT, GL_FALSE, 4*sizeof(float), 0);
    glEnableVertexAttribArray(posAttrib);
    glVertexAttribPointer(texCoordAttrib, 2, GL_FLOAT, GL_FALSE, 4*sizeof(float), (void*)(2*sizeof(float)));
    glEnableVertexAttribArray(texCoordAttrib);
}

void MenuState::createVertexBuffer()
{
    m_VertexBuffer.init();
    m_VertexBuffer.bind();
    m_VertexBuffer.setData(
        {
            -1.f, -1.f, 0.f, 1.f,
            1.f, -1.f, 1.f, 1.f,
            1.f, 1.f, 1.f, 0.f,
            1.f, 1.f, 1.f, 0.f,
            -1.f, 1.f, 0.f, 0.f,
            -1.f, -1.f, 0.f, 1.f
        });
}

void MenuState::createTexture()
{
    glActiveTexture(GL_TEXTURE0);
    glGenTextures(1, &m_Texture);
    glBindTexture(GL_TEXTURE_2D, m_Texture);

    setTextureWrapping();
    setTextureFiltering();

    glGenerateMipmap(GL_TEXTURE_2D);

    auto textureData = loadTextureData();

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_TextureWidth, m_TextureHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, textureData);

    SOIL_free_image_data(textureData);
}

unsigned char* MenuState::loadTextureData()
{
    return SOIL_load_image(m_TextureFileName.c_str(), &m_TextureWidth, &m_TextureHeight, 0, SOIL_LOAD_RGB);
}

void MenuState::setTextureWrapping()
{
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
}

void MenuState::setTextureFiltering()
{
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
}

void MenuState::keyPressed(unsigned char key, int x, int y)
{
    m_Game->startPlaying();
}

void MenuState::update(int delta)
{

}

void MenuState::display()
{
    m_VertexBuffer.bind();
    m_Game->getShaderManager().useShader("Texture");

    setupVertexAttrib();
    passTextureToShader();
    passMatrixToShader();

    glDrawArrays(GL_TRIANGLES, 0, 12);
}
