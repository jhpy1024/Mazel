#include "Map.hpp"

#include <fstream>
#include <iostream>
#include <algorithm>

#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Utils.hpp"
#include "Game.hpp"

Map::Map(const std::string& file, Game* game)
    : m_FileName(file)
    , m_Game(game)
    , m_ModelMatrix(1.f)
{

}

void Map::init()
{
    m_Game->getShaderManager().useShader("Simple");

    addTileTypesToMap();

    parseFile();

    setupVertices();
    setupVertexBuffer();
    setupVertexAttrib();

    setupColors();
    setupColorBuffer();
    setupColorAttrib();
}

void Map::addTileTypesToMap()
{
    Tile tile;

    tile.color = glm::vec4(0.1f, 0.1f, 0.1f, 1.f);
    tile.isCollidable = true;
    m_TileTypes[DarkTile] = tile;

    tile.color = glm::vec4(0.3f, 0.3f, 0.3f, 1.f);
    tile.isCollidable = false;
    m_TileTypes[GrayTile] = tile;

    tile.color = glm::vec4(1.f, 1.f, 1.f, 1.f);
    tile.isCollidable = false;
    m_TileTypes[WhiteTile] = tile;
}

void Map::display()
{
    m_Game->getShaderManager().useShader("Simple");

    setModelMatrix();
    setupVertexAttrib();
    setupColorAttrib();
    glDrawArrays(GL_TRIANGLES, 0, m_Vertices.size());
}

void Map::setModelMatrix()
{
    auto mvpMatrix = m_Game->getProjectionMatrix() * m_Game->getViewMatrix() * m_ModelMatrix;

    auto mvpLocation = m_Game->getShaderManager().getShader("Simple")->getUniformLocation("in_MvpMatrix");
    glUniformMatrix4fv(mvpLocation, 1, GL_FALSE, glm::value_ptr(mvpMatrix));
}

void Map::setupVertices()
{
    for (int y = m_Height - 1; y >= 0; --y)
    {
        for (int x = 0; x < m_Height; ++x)
        {
            createBottomLeftVertex(x, y);
            createBottomRightVertex(x, y);
            createTopRightVertex(x, y);
            createTopRightVertex(x, y);
            createTopLeftVertex(x, y);
            createBottomLeftVertex(x, y);
        }
    }
}

void Map::createTopLeftVertex(int x, int y)
{
    m_Vertices.insert(m_Vertices.end(),
        {x * m_TileWidth, y * m_TileHeight + m_TileHeight});
}

void Map::createTopRightVertex(int x, int y)
{
    m_Vertices.insert(m_Vertices.end(),
        {x * m_TileWidth + m_TileWidth, y * m_TileHeight + m_TileHeight});
}

void Map::createBottomRightVertex(int x, int y)
{
    m_Vertices.insert(m_Vertices.end(),
        {x * m_TileHeight + m_TileWidth, y * m_TileHeight});
}

void Map::createBottomLeftVertex(int x, int y)
{
    m_Vertices.insert(m_Vertices.end(),
        {x * m_TileWidth, y * m_TileHeight});
}

void Map::setupVertexBuffer()
{
    m_VertexBuffer.init();
    m_VertexBuffer.setData(m_Vertices);
}

void Map::setupVertexAttrib()
{
    m_VertexBuffer.bind();
    auto posAttrib = m_Game->getShaderManager().getShader("Simple")->getAttribLocation("in_Position");
    glEnableVertexAttribArray(posAttrib);
    glVertexAttribPointer(posAttrib, 2, GL_FLOAT, GL_FALSE, 0, 0);
}

void Map::setupColors()
{
    for (auto t : m_Tiles)
    {
        for (int i = 0; i < 6; ++i)
            m_Colors.insert(m_Colors.end(), {t.color.x, t.color.y, t.color.z, t.color.w});
    }
}

void Map::setupColorBuffer()
{
    m_ColorBuffer.init();
    m_ColorBuffer.setData(m_Colors);
}

void Map::setupColorAttrib()
{
    m_ColorBuffer.bind();
    auto colorAttrib = m_Game->getShaderManager().getShader("Simple")->getAttribLocation("in_Color");
    glEnableVertexAttribArray(colorAttrib);
    glVertexAttribPointer(colorAttrib, 4, GL_FLOAT, GL_FALSE, 0, 0);
}

void Map::parseFile()
{
    std::string currentLine;

    std::ifstream fileStream(m_FileName);

    if (fileStream.is_open())
    {
        while (std::getline(fileStream, currentLine))
        {
            parseVariable(m_Width, "width", currentLine);
            parseVariable(m_Height, "height", currentLine);
            parseVariable(m_TileWidth, "tilewidth", currentLine);
            parseVariable(m_TileHeight, "tileheight", currentLine);

            parseTiles(currentLine);
        }
    }
    else
    {
        std::cerr << "Error loading map file: " << m_FileName << std::endl;
    }
}

void Map::parseVariable(int& var, const std::string& varName, const std::string& line)
{
    auto varSubString = line.substr(0, varName.size());

    if (varSubString == varName)
    {
        auto colonPos = line.find(':');

        if (colonPos == line.npos)
            std::cerr << "Error parsing variable: " << varName << ". Missing colon seperator" << std::endl;

        auto value = line.substr(colonPos + 1);
        var = util::stringToNum<int>(value);
    }
}

void Map::parseTiles(const std::string& line)
{
    // If the line contains a comma we assume that this
    // is a line containing tiles.
    if (line.find(',') != line.npos)
    {
        auto commaPos = line.find_first_of(',');
        auto firstTileStr = line.substr(0, commaPos);
        auto firstTileNum = util::stringToNum<int>(firstTileStr);
        m_Tiles.push_back(m_TileTypes[firstTileNum]);

        while (commaPos != line.npos)
        {
            std::string tileStr;
            auto nextCommaPos = line.find_first_of(',', commaPos + 1);

            if (nextCommaPos == line.npos)
                tileStr = line.substr(commaPos + 1);
            else
                tileStr = line.substr(commaPos + 1, nextCommaPos - 1);

            auto tileNum = util::stringToNum<int>(tileStr);
            m_Tiles.push_back(m_TileTypes[tileNum]);

            commaPos = nextCommaPos;
        }
    }
}

bool Map::isTileAtPixelPosCollidable(glm::vec2 position) const
{
    return getTileAtPixelPos(position).isCollidable;
}

bool Map::isTileAtTilePosCollidable(glm::vec2 position) const
{
    return getTileAtTilePos(position).isCollidable;
}

Tile Map::getTileAtPixelPos(glm::vec2 position) const
{
    glm::vec2 tilePosition = position / glm::vec2(m_TileWidth, m_TileHeight);

    return getTileAtTilePos(tilePosition);
}

Tile Map::getTileAtTilePos(glm::vec2 position) const
{
    int index = static_cast<float>(((m_Height - 1) - position.y) * m_Width + position.x);

    return m_Tiles.at(index);
}

int Map::getWidth() const
{
    return m_Width;
}

int Map::getHeight() const
{
    return m_Height;
}

int Map::getTileWidth() const
{
    return m_TileWidth;
}

int Map::getTileHeight() const
{
    return m_TileHeight;
}
