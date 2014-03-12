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
    GLuint m_Texture;

    Buffer m_VertexBuffer;
};

#endif // MENU_STATE_HPP
