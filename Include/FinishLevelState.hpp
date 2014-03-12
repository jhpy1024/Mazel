#ifndef FINISH_LEVEL_STATE_HPP
#define FINISH_LEVEL_STATE_HPP

#include "GameState.hpp"

#include <string>

#include <GL/glew.h>
#include <GL/gl.h>

#include "Buffer.hpp"

class FinishLevelState : public GameState
{
public:
    FinishLevelState(Game* game);
    ~FinishLevelState();

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

#endif // FINISH_LEVEL_STATE_HPP
