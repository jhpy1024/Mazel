#ifndef MAP_HPP
#define MAP_HPP

#include <string>
#include <vector>

#include <GL/glew.h>
#include <GL/gl.h>

class Map
{
public:
    Map(const std::string& file);

    int getWidth() const;
    int getHeight() const;
    int getTileWidth() const;
    int getTileHeight() const;

private:
    void parseFile(const std::string& file);
    void parseVariable(int& var, const std::string& varName, const std::string& line);
    void parseTiles(const std::string& line);

private:
    GLuint m_VertexBuffer;
    GLuint m_ColorBuffer;

    int m_Width;
    int m_Height;
    int m_TileWidth;
    int m_TileHeight;

    // (x, y) = m_Tiles[y * num cols + x]
    std::vector<int> m_Tiles;
};

#endif // MAP_HPP
