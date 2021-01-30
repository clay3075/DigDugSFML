//
// Created by Clay Reddick on 1/26/21.
//

#ifndef SFMLTILEMAP_TILEMAPRENDERER_H
#define SFMLTILEMAP_TILEMAPRENDERER_H
#include "TileMap.h"
#include <SFML/Graphics.hpp>
#include "TileRenderer.h"

class TileMapRenderer {
public:
    TileMapRenderer(sf::RenderWindow* window, TileMap* map) { _window = window; _tileMap = map; }
    void draw();
private:
    sf::RenderWindow* _window;
    TileMap* _tileMap;
};

#endif //SFMLTILEMAP_TILEMAPRENDERER_H
