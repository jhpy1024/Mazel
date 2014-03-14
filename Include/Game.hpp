#ifndef GAME_HPP
#define GAME_HPP

#define GLM_FORCE_RADIANS

#include <glm/glm.hpp>
#include <GL/glew.h>
#include <GL/gl.h>

#include "ShaderManager.hpp"
#include "Map.hpp"
#include "Entity.hpp"
#include "TestEntity.hpp"
#include "Projectile.hpp"
#include "GameState.hpp"

#include <vector>
#include <memory>

class Game
{
public:
    Game(int width, int height);

    void init();

    void keyPressed(unsigned char key, int x, int y);
    void keyReleased(unsigned char key, int x, int y);
    void mouseEvent(int button, int state, int x, int y);
    void specialKeyPressed(int key, int x, int y);
    void specialKeyReleased(int key, int x, int y);

    void update(int delta);
    void display();

    void resize(int width, int height);

    Map& getMap();
    ShaderManager& getShaderManager();

    glm::mat4 getProjectionMatrix() const;
    glm::mat4 getViewMatrix() const;

    void createTestEntity(glm::vec2 position, glm::vec2 size);
    void createProjectile(glm::vec2 position, glm::vec2 size, float angle);

    std::shared_ptr<TestEntity>& getPlayer();
    std::vector<std::shared_ptr<Entity>>& getEntities();
    std::vector<std::shared_ptr<Projectile>>& getProjectiles();

    void changeState(std::shared_ptr<GameState> state);

    void startPlaying();
    void finishedLevel();
    void nextLevel();
    void restartGame();
    void quit();

private:
    void loadShaders();
    void setupMatrices();

    void addNewEntities();
    void resetEntities();

    void changeMapToNextLevel();

private:
    int m_Width;
    int m_Height;

    glm::mat4 m_ProjMatrix;
    glm::mat4 m_ViewMatrix;
    glm::mat4 m_ModelMatrix;
    glm::mat4 m_MvpMatrix;

    ShaderManager m_ShaderManager;

    int m_CurrentMap;
    const int m_NumMaps;
    Map m_TestMap;

    std::shared_ptr<TestEntity> m_TestEntity;

    std::vector<std::shared_ptr<Entity>> m_Entities;
    std::vector<std::shared_ptr<Entity>> m_EntitiesToAdd;
    std::vector<std::shared_ptr<Projectile>> m_Projectiles;

    std::shared_ptr<GameState> m_CurrentState;

    const glm::vec2 m_PlayerStartPosition;
    const glm::vec2 m_PlayerSize;
};

#endif // GAME_HPP
