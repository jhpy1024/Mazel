#ifndef GAME_HPP
#define GAME_HPP

#include "ShaderManager.hpp"

// Get rid of GLM's deprecated compile messages
#define GLM_FORCE_RADIANS

#include <glm/glm.hpp>

class Game
{
public:
    Game(int width, int height);

    void setupGL();

    void keyPressed(unsigned char key, int x, int y);
    void specialKeyPressed(int key, int x, int y);
    void specialKeyReleased(int key, int x, int y);
    void mousePressed(int button, int state, int x, int y);

    void update(int delta);
    void render();

private:
    void createShaders();

private:
    ShaderManager m_ShaderManager;

    glm::mat4 m_ProjMatrix;
    glm::mat4 m_ViewMatrix;
    glm::mat4 m_ModelMatrix;
    glm::mat4 m_MvpMatrix;

    const int m_Width;
    const int m_Height;
};

#endif // GAME_HPP
