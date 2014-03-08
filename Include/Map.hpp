#ifndef MAP_HPP
#define MAP_HPP

#include <string>
#include <vector>

#include <GL/glew.h>
#include <GL/gl.h>

#include <glm/glm.hpp>

#include "ShaderManager.hpp"

enum Tile
{
    DarkTile,
    GrayTile,
    WhiteTile,
};

class Game;
class Map
{
public:
    Map(const std::string& file, Game* game);

    int getWidth() const;
    int getHeight() const;
    int getTileWidth() const;
    int getTileHeight() const;

    void init();
    void display();

private:
    void parseFile();
    void parseVariable(int& var, const std::string& varName, const std::string& line);
    void parseTiles(const std::string& line);

    void setupVertices();
    void setupVertexBuffer();
    void setupVertexAttrib();

    void setupColors();
    void setupColorBuffer();
    void setupColorAttrib();

    void createBottomLeftVertex(int x, int y);
    void createBottomRightVertex(int x, int y);
    void createTopLeftVertex(int x, int y);
    void createTopRightVertex(int x, int y);

    void setModelMatrix();

private:
    GLuint m_VertexBuffer;
    GLuint m_ColorBuffer;

    int m_Width;
    int m_Height;
    int m_TileWidth;
    int m_TileHeight;

    std::vector<float> m_Vertices;
    std::vector<float> m_Colors;

    std::vector<int> m_Tiles;

    std::string m_FileName;

    Game* m_Game;

    glm::mat4 m_ModelMatrix;
};

#endif // MAP_HPP
