#include "Map.hpp"

#include <fstream>
#include <iostream>

#include "Utils.hpp"

Map::Map(const std::string& file, ShaderManager& shaderManager)
    : m_FileName(file)
    , m_ShaderManager(shaderManager)
{

}

void Map::init()
{
    parseFile();

    m_ShaderManager.useShader("Simple");

    setupVertices();
    setupColors();
}

void Map::display()
{
    glDrawArrays(GL_TRIANGLES, 0, m_Vertices.size());
}

void Map::setupVertices()
{
    for (int x = 0; x < m_Width; ++x)
    {
        for (int y = 0; y < m_Height; ++y)
        {
            // Bottom left vertex
            m_Vertices.insert(m_Vertices.end(),
                {x * m_TileWidth, y * m_TileHeight});

            // Bottom right vertex
            m_Vertices.insert(m_Vertices.end(),
                {x * m_TileHeight + m_TileWidth, y * m_TileHeight});

            // Top right vertex
            m_Vertices.insert(m_Vertices.end(),
                {x * m_TileWidth + m_TileWidth, y * m_TileHeight + m_TileHeight});

            // Top right vertex
            m_Vertices.insert(m_Vertices.end(),
                {x * m_TileWidth + m_TileWidth, y * m_TileHeight + m_TileHeight});

            // Top left vertex
            m_Vertices.insert(m_Vertices.end(),
                {x * m_TileWidth, y * m_TileHeight + m_TileHeight});

            // Bottom left vertex
            m_Vertices.insert(m_Vertices.end(),
                {x * m_TileWidth, y * m_TileHeight});
        }
    }

    glGenBuffers(1, &m_VertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, m_VertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * m_Vertices.size(), &m_Vertices[0], GL_STATIC_DRAW);

    auto posAttrib = m_ShaderManager.getShader("Simple")->getAttribLocation("in_Position");
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

    glGenBuffers(1, &m_ColorBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, m_ColorBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * m_Colors.size(), &m_Colors[0], GL_STATIC_DRAW);

    auto colorAttrib = m_ShaderManager.getShader("Simple")->getAttribLocation("in_Color");
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
    if (line.substr(0, varName.size()) == varName)
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
