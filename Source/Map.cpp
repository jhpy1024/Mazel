#include "Map.hpp"

#include <fstream>
#include <iostream>

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
    parseFile();

    m_Game->getShaderManager().useShader("Simple");

    setupVertices();
    setupVertexBuffer();
    setupVertexAttrib();

    setupColors();
    setupColorBuffer();
    setupColorAttrib();
}

void Map::display()
{
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
    glGenBuffers(1, &m_VertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, m_VertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * m_Vertices.size(), &m_Vertices[0], GL_STATIC_DRAW);
}

void Map::setupVertexAttrib()
{
    glBindBuffer(GL_ARRAY_BUFFER, m_VertexBuffer);
    auto posAttrib = m_Game->getShaderManager().getShader("Simple")->getAttribLocation("in_Position");
    glEnableVertexAttribArray(posAttrib);
    glVertexAttribPointer(posAttrib, 2, GL_FLOAT, GL_FALSE, 0, 0);
}

void Map::setupColors()
{
    for (auto t : m_Tiles)
    {
        switch (t)
        {
        case RedTile:
            m_Colors.insert(m_Colors.end(),
                {1.f, 0.f, 0.f, 1.f, 1.f, 0.f, 0.f, 1.f, 1.f, 0.f, 0.f, 1.f, 1.f, 0.f, 0.f, 1.f, 1.f, 0.f, 0.f, 1.f, 1.f, 0.f, 0.f, 1.f});
            break;
        case GreenTile:
            m_Colors.insert(m_Colors.end(),
                {0.f, 1.f, 0.f, 1.f, 0.f, 1.f, 0.f, 1.f, 0.f, 1.f, 0.f, 1.f, 0.f, 1.f, 0.f, 1.f, 0.f, 1.f, 0.f, 1.f, 0.f, 1.f, 0.f, 1.f});
            break;
        case BlueTile:
            m_Colors.insert(m_Colors.end(),
                {0.f, 0.f, 1.f, 1.f, 0.f, 0.f, 1.f, 1.f, 0.f, 0.f, 1.f, 1.f, 0.f, 0.f, 1.f, 1.f, 0.f, 0.f, 1.f, 1.f, 0.f, 0.f, 1.f, 1.f});
            break;
        default:
            break;
        }
    }
}

void Map::setupColorBuffer()
{
    glGenBuffers(1, &m_ColorBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, m_ColorBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * m_Colors.size(), &m_Colors[0], GL_STATIC_DRAW);
}

void Map::setupColorAttrib()
{
    glBindBuffer(GL_ARRAY_BUFFER, m_ColorBuffer);
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
        m_Tiles.push_back(util::stringToNum<int>(firstTileStr));

        while (commaPos != line.npos)
        {
            std::string tileStr;
            auto nextCommaPos = line.find_first_of(',', commaPos + 1);

            if (nextCommaPos == line.npos)
                tileStr = line.substr(commaPos + 1);
            else
                tileStr = line.substr(commaPos + 1, nextCommaPos - 1);

            m_Tiles.push_back(util::stringToNum<int>(tileStr));

            commaPos = nextCommaPos;
        }
    }
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
