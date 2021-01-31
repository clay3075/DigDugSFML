//
// Created by Clay Reddick on 1/26/21.
//

#ifndef SFMLTILEMAP_TILERENDERER_H
#define SFMLTILEMAP_TILERENDERER_H
#include <SFML/Graphics.hpp>
#include <map>
#include <string>
#include "Tile.h"

class TileRenderer {
public:
    TileRenderer() = default;
    TileRenderer(sf::RenderWindow* window, Tile* tile) { _window = window; _tile = tile; }
    void draw();
    static std::map<std::string, sf::Texture> textures;
private:
    sf::RenderWindow* _window;
    Tile* _tile;
    sf::Texture getTexture(std::string id);
};


#endif //SFMLTILEMAP_TILERENDERER_H
