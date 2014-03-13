#ifndef WIN_GAME_STATE_HPP
#define WIN_GAME_STATE_HPP

#include "GameState.hpp"

#include <GL/glew.h>
#include <GL/gl.h>

#include <string>

#include "Buffer.hpp"

class WinGameState : public GameState
{
public:
    WinGameState(Game* game);
    ~WinGameState();

    void keyPressed(unsigned char key, int x, int y) override;

    void update(int delta) override;
    void display() override;

private:
    void createTexture();
    void setTextureWrapping();
    void setTextureFiltering();
    unsigned char* loadTextureData();

    void createVertexBuffer();
    void setupVertexAttrib();

    void passTextureToShader();
    void passMatrixToShader();

private:
    GLuint m_Texture;
    int m_TextureWidth;
    int m_TextureHeight;
    const std::string m_TextureFileName;

    Buffer m_VertexBuffer;
};

#endif // WIN_GAME_STATE_HPP
