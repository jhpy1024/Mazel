#ifndef ENTITY_HPP
#define ENTITY_HPP

#include <GL/glew.h>
#include <GL/gl.h>

#include <vector>

#include <glm/glm.hpp>

class Game;
class Entity
{
public:
    Entity(Game* game, glm::vec2 position, glm::vec2 size);

    void init();

    virtual void setupVertices() = 0;
    virtual void setupColors() = 0;

    virtual void setupVertexBuffer() = 0;
    virtual void setupColorBuffer() = 0;

    virtual void update(int delta) = 0;
    virtual void display() = 0;

    void setPosition(glm::vec2 position);
    void setSize(glm::vec2 size);

    glm::vec2 getPosition() const;
    glm::vec2 getSize() const;

protected:
    Game* m_Game;

    GLuint m_VertexBuffer;
    GLuint m_ColorBuffer;

    std::vector<float> m_Vertices;
    std::vector<float> m_Colors;

    glm::vec2 m_Position;
    glm::vec2 m_Size;
};

#endif // ENTITY_HPP
