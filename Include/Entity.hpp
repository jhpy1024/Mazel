#ifndef ENTITY_HPP
#define ENTITY_HPP

#include <GL/glew.h>
#include <GL/gl.h>

#include <vector>
#include <string>

#include <glm/glm.hpp>

class Game;
class Entity
{
public:
    Entity(Game* game, glm::vec2 position, glm::vec2 size, const std::string& id);
    virtual ~Entity();

    void init();

    virtual void setupVertices() = 0;
    virtual void setupColors() = 0;

    virtual void setupVertexBuffer() = 0;
    virtual void setupColorBuffer() = 0;

    virtual void setupVertexAttrib() = 0;
    virtual void setupColorAttrib() = 0;

    virtual void keyEvent(unsigned char key);
    virtual void specialKeyPressed(int key);
    virtual void specialKeyReleased(int key);

    virtual void update(int delta);
    virtual void display() = 0;

    void setPosition(glm::vec2 position);
    void setSize(glm::vec2 size);

    glm::vec2 getPosition() const;
    glm::vec2 getSize() const;

    std::string getID() const;

protected:
    void updateMatrices();
    void passMatrixToShader();

protected:
    Game* m_Game;

    GLuint m_VertexBuffer;
    GLuint m_ColorBuffer;

    std::vector<float> m_Vertices;
    std::vector<float> m_Colors;

    glm::vec2 m_Position;
    glm::vec2 m_Size;
    glm::vec2 m_Scale;
    float m_Rotation;

    glm::mat4 m_TranslationMatrix;
    glm::mat4 m_RotationMatrix;
    glm::mat4 m_ScaleMatrix;
    glm::mat4 m_ModelMatrix;

    std::string m_ID;
};

#endif // ENTITY_HPP
