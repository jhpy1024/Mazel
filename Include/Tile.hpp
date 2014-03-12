#ifndef TILE_HPP
#define TILE_HPP

#include <glm/glm.hpp>

struct Tile
{
    bool isCollidable = false;
    bool isFinishTile = false;

    glm::vec4 color;
};

#endif // TILE_HPP
