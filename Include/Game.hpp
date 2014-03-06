#ifndef GAME_HPP
#define GAME_HPP

#define GLM_FORCE_RADIANS

#include <glm/glm.hpp>
#include <GL/glew.h>
#include <GL/gl.h>

#include "ShaderManager.hpp"
#include "Map.hpp"
#include "TestEntity.hpp"

#include <vector>

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

    // ====== Getters ======
    const Map& getMap() const;
    ShaderManager& getShaderManager();
    // =====================

private:
    void loadShaders();
    void setupMatrices();

private:
    int m_Width;
    int m_Height;

    glm::mat4 m_ProjMatrix;
    glm::mat4 m_ViewMatrix;
    glm::mat4 m_ModelMatrix;
    glm::mat4 m_MvpMatrix;

    ShaderManager m_ShaderManager;

    Map m_TestMap;
};

#endif // GAME_HPP
