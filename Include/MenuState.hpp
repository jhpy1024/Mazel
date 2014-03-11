#ifndef MENU_STATE_HPP
#define MENU_STATE_HPP

#include "GameState.hpp"
#include "Buffer.hpp"

#include <GL/glew.h>
#include <GL/gl.h>

#include <string>

class MenuState : public GameState
{
public:
    MenuState(Game* game);

    void keyPressed(unsigned char key, int x, int y) override;

    void update(int delta) override;
    void display() override;

private:
    void setupVertexBuffer();
    void setupVertexAttrib();
    void setupTexCoordBuffer();
    void setupTexCoordAttrib();

    void createTexture();
    void setTextureWrapping();
    void setTextureFiltering();
    void generateTextureMipmap();
    unsigned char* loadTextureData();

    void updateMatrices();

private:
    Buffer m_VertexBuffer;
    Buffer m_TexCoordBuffer;

    GLuint m_Texture;
    int m_TextureWidth;
    int m_TextureHeight;
    const std::string m_TextureFileName;
};

#endif // MENU_STATE_HPP
