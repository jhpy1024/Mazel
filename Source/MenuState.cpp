#include "MenuState.hpp"

#include <SOIL.h>

#include <iostream>

#include "Game.hpp"

MenuState::MenuState(Game* game)
    : GameState(game)
    , m_TextureFileName("Textures/menuScreen.png")
{
    m_Game->getShaderManager().useShader("Texture");
    createTexture();

    setupVertexBuffer();
    setupVertexAttrib();
    setupTexCoordBuffer();
    setupTexCoordAttrib();
}

void MenuState::setupVertexBuffer()
{

    auto textureWidth = static_cast<float>(m_TextureWidth);
    auto textureHeight = static_cast<float>(m_TextureHeight);

    m_VertexBuffer.init();
    m_VertexBuffer.bind();
    m_VertexBuffer.setData(
        {
            0.f, 0.f,
            textureWidth, 0.f,
            textureWidth, textureHeight,
            textureWidth, textureHeight,
            0.f, textureHeight,
            0.f, 0.f
        });

    std::cout << "Texture dimensions = (" << textureWidth << ", " << textureHeight << ")" << std::endl;
}

void MenuState::setupTexCoordBuffer()
{
    m_TexCoordBuffer.init();
    m_TexCoordBuffer.bind();
    m_TexCoordBuffer.setData(
        {
            0.f, 0.f,
            1.f, 0.f,
            0.f, 1.f,
            1.f, 0.f,
            1.f, 1.f,
            0.f, 1.f
        });
}

void MenuState::setupVertexAttrib()
{
    m_VertexBuffer.bind();
    auto posAttrib = m_Game->getShaderManager().getShader("Texture")->getAttribLocation("in_Position");
    glEnableVertexAttribArray(posAttrib);
    glVertexAttribPointer(posAttrib, 2, GL_FLOAT, GL_FALSE, 0, 0);
}

void MenuState::setupTexCoordAttrib()
{
    m_TexCoordBuffer.bind();
    auto texCoordAttrib = m_Game->getShaderManager().getShader("Texture")->getAttribLocation("in_TexCoord");
    glEnableVertexAttribArray(texCoordAttrib);
    glVertexAttribPointer(texCoordAttrib, 2, GL_FLOAT, GL_FALSE, 0, 0);
}

void MenuState::createTexture()
{
    glGenTextures(1, &m_Texture);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, m_Texture);

    auto textureData = loadTextureData();

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_TextureWidth, m_TextureHeight, 0, GL_RGB,
              GL_UNSIGNED_BYTE, textureData);

    setTextureWrapping();
    setTextureFiltering();
    generateTextureMipmap();

    auto textureLocation = m_Game->getShaderManager().getShader("Texture")->getUniformLocation("in_Texture");
    glUniform1i(textureLocation, 0);
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

void MenuState::generateTextureMipmap()
{
    glGenerateMipmap(GL_TEXTURE_2D);
}

unsigned char* MenuState::loadTextureData()
{
    auto textureData = SOIL_load_image(m_TextureFileName.c_str(), &m_TextureWidth, &m_TextureHeight, 0, SOIL_LOAD_RGB);
    return textureData;
}

void MenuState::keyPressed(unsigned char key, int x, int y)
{

}

void MenuState::update(int delta)
{

}

void MenuState::display()
{
    m_Game->getShaderManager().useShader("Texture");

    updateMatrices();
    setupVertexAttrib();
    setupTexCoordAttrib();
    glDrawArrays(GL_TRIANGLES, 0, m_VertexBuffer.getDataSize());
}

void MenuState::updateMatrices()
{
    auto projectionMatrix = m_Game->getProjectionMatrix();
    auto viewMatrix = m_Game->getViewMatrix();

    auto mvpMatrix = projectionMatrix * viewMatrix;
    auto mvpLocation = m_Game->getShaderManager().getShader("Texture")->getUniformLocation("in_MvpMatrix");
}
