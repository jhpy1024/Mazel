#ifndef MAP_HPP
#define MAP_HPP

#include <string>
#include <vector>

#include <GL/glew.h>
#include <GL/gl.h>

#include "ShaderManager.hpp"

enum Tile
{
    RedTile,
    GreenTile,
    BlueTile,
};

class Map
{
public:
    Map(const std::string& file, ShaderManager& shaderManager);

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

    void setupColors();
    void setupColorBuffer();

    void createBottomLeftVertex(int x, int y);
    void createBottomRightVertex(int x, int y);
    void createTopLeftVertex(int x, int y);
    void createTopRightVertex(int x, int y);

private:
    GLuint m_VertexBuffer;
    GLuint m_ColorBuffer;

    int m_Width;
    int m_Height;
    int m_TileWidth;
    int m_TileHeight;

    std::vector<float> m_Vertices;
    std::vector<float> m_Colors;

    // If (0,0) is the bottom left of a tile:
    // -> the tile at (x,y) is m_Tiles[(m_Height - y) * m_Width + x]
    std::vector<int> m_Tiles;

    std::string m_FileName;

    ShaderManager& m_ShaderManager;
};

#endif // MAP_HPP
