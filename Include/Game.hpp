#ifndef GAME_HPP
#define GAME_HPP

#define GLM_FORCE_RADIANS

#include <glm/glm.hpp>
#include <GL/glew.h>
#include <GL/gl.h>

#include "ShaderManager.hpp"

class Game
{
public:
    Game(int width, int height);

    void init();

    void keyEvent(unsigned char key, int x, int y);
    void mouseEvent(int button, int state, int x, int y);
    void specialKeyPressed(int key, int x, int y);
    void specialKeyReleased(int key, int x, int y);

    void update(int delta);
    void display();

    void resize(int width, int height);

private:
    int m_Width;
    int m_Height;

    glm::mat4 m_ProjMatrix;
    glm::mat4 m_ViewMatrix;
    glm::mat4 m_ModelMatrix;
    glm::mat4 m_MvpMatrix;

    GLuint m_VertexBuffer;
    GLuint m_ColorBuffer;

    ShaderManager m_ShaderManager;
};

#endif // GAME_HPP
