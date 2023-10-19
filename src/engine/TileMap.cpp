#include "TileMap.h"

void TileMap::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    states.transform *= getTransform();
    states.texture = &m_tileset;
    target.draw(m_vertices, states);
}


bool TileMap::load(const string& tileset, sf::Vector2u tileSize, const vector<vector<int>>& tiles)
{
    if (!m_tileset.loadFromFile(tileset))
        return false;

    const unsigned int width = tiles[0].size();
    const unsigned int height = tiles.size();

    m_vertices.setPrimitiveType(sf::Triangles);
    m_vertices.resize(width * height * 6);

    for (unsigned int i = 0; i < width; ++i)
    {
        for (unsigned int j = 0; j < height; ++j)
        {
            int tileNumber = tiles[j][i] - 1;

            if (tileNumber < 0) {
                continue;
            }

            int tu = tileNumber % (m_tileset.getSize().x / tileSize.x);
            int tv = tileNumber / (m_tileset.getSize().x / tileSize.x);

            sf::Vertex* triangles = &m_vertices[(i + j * width) * 6];

            triangles[0].position = sf::Vector2f(i * tileSize.x, j * tileSize.y);
            triangles[1].position = sf::Vector2f((i + 1) * tileSize.x, j * tileSize.y);
            triangles[2].position = sf::Vector2f(i * tileSize.x, (j + 1) * tileSize.y);
            triangles[3].position = sf::Vector2f(i * tileSize.x, (j + 1) * tileSize.y);
            triangles[4].position = sf::Vector2f((i + 1) * tileSize.x, j * tileSize.y);
            triangles[5].position = sf::Vector2f((i + 1) * tileSize.x, (j + 1) * tileSize.y);

            triangles[0].texCoords = sf::Vector2f(tu * tileSize.x, tv * tileSize.y);
            triangles[1].texCoords = sf::Vector2f((tu + 1) * tileSize.x, tv * tileSize.y);
            triangles[2].texCoords = sf::Vector2f(tu * tileSize.x, (tv + 1) * tileSize.y);
            triangles[3].texCoords = sf::Vector2f(tu * tileSize.x, (tv + 1) * tileSize.y);
            triangles[4].texCoords = sf::Vector2f((tu + 1) * tileSize.x, tv * tileSize.y);
            triangles[5].texCoords = sf::Vector2f((tu + 1) * tileSize.x, (tv + 1) * tileSize.y);
        }
    }

    this->tiles = tiles;

    return true;
}

const vector<vector<int>>& TileMap::getTiles() const
{
    return tiles;
}

int TileMap::getTileValue(unsigned int x, unsigned int y) const
{
    if (x < tiles[0].size() && y < tiles.size()) {
        return tiles[y][x];
    }
    return -1;
}

void TileMap::setGravity(float gravity)
{
    this->gravity = gravity;
}

float TileMap::getGravity()
{
    return gravity;
}
