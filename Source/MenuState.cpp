#include "MenuState.hpp"

#include <SOIL.h>

#include <iostream>

#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Game.hpp"

MenuState::MenuState(Game* game)
    : GameState(game)
{
    glActiveTexture(GL_TEXTURE0);

    glGenTextures(1, &m_Texture);
    glBindTexture(GL_TEXTURE_2D, m_Texture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glGenerateMipmap(GL_TEXTURE_2D);

    int textureWidth;
    int textureHeight;
    unsigned char* textureData = SOIL_load_image("menuScreen.png", &textureWidth, &textureHeight, 0, SOIL_LOAD_RGB);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, textureWidth, textureHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, textureData);

    SOIL_free_image_data(textureData);

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


    m_Game->getShaderManager().useShader("Texture");

    auto posAttrib = m_Game->getShaderManager().getShader("Texture")->getAttribLocation("in_Position");
    auto texCoordAttrib = m_Game->getShaderManager().getShader("Texture")->getAttribLocation("in_TexCoord");

    glVertexAttribPointer(posAttrib, 2, GL_FLOAT, GL_FALSE, 4*sizeof(float), 0);
    glEnableVertexAttribArray(posAttrib);
    glVertexAttribPointer(texCoordAttrib, 2, GL_FLOAT, GL_FALSE, 4*sizeof(float), (void*)(2*sizeof(float)));
    glEnableVertexAttribArray(texCoordAttrib);

    auto texLocation = m_Game->getShaderManager().getShader("Texture")->getUniformLocation("in_Texture");
    glUniform1i(texLocation, GL_TEXTURE0);

    auto mvpLocation = m_Game->getShaderManager().getShader("Texture")->getUniformLocation("in_MvpMatrix");
    glUniformMatrix4fv(mvpLocation, 1, GL_FALSE, glm::value_ptr(glm::mat4(1.f)));
}

void MenuState::keyPressed(unsigned char key, int x, int y)
{

}

void MenuState::update(int delta)
{

}

void MenuState::display()
{
    glActiveTexture(GL_TEXTURE0);
    m_VertexBuffer.bind();
    m_Game->getShaderManager().useShader("Texture");

    auto posAttrib = m_Game->getShaderManager().getShader("Texture")->getAttribLocation("in_Position");
    auto texCoordAttrib = m_Game->getShaderManager().getShader("Texture")->getAttribLocation("in_TexCoord");

    auto texLocation = m_Game->getShaderManager().getShader("Texture")->getUniformLocation("in_Texture");
    glUniform1i(texLocation, GL_TEXTURE0);

    auto mvpLocation = m_Game->getShaderManager().getShader("Texture")->getUniformLocation("in_MvpMatrix");
    glUniformMatrix4fv(mvpLocation, 1, GL_FALSE, glm::value_ptr(glm::mat4(1.f)));

    glVertexAttribPointer(posAttrib, 2, GL_FLOAT, GL_FALSE, 4*sizeof(float), 0);
    glEnableVertexAttribArray(posAttrib);
    glVertexAttribPointer(texCoordAttrib, 2, GL_FLOAT, GL_FALSE, 4*sizeof(float), (void*)(2*sizeof(float)));
    glEnableVertexAttribArray(texCoordAttrib);

    glDrawArrays(GL_TRIANGLES, 0, 12);

    //std::cout << glGetError() << std::endl;
}
