#include "Map.hpp"

#include <fstream>
#include <iostream>

#include "Utils.hpp"

Map::Map(const std::string& file)
{
    parseFile(file);

    std::cout << "== Loaded map ==" << std::endl;
    std::cout << "Width: " << m_Width << std::endl;
    std::cout << "Height: " << m_Height << std::endl;
    std::cout << "Tile Width: " << m_TileWidth << std::endl;
    std::cout << "Tile Height: " << m_TileHeight << std::endl;
    std::cout << "================" << std::endl;
}

void Map::parseFile(const std::string& file)
{
    std::string currentLine;

    std::ifstream fileStream(file);

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
        std::cerr << "Error loading map file: " << file << std::endl;
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
