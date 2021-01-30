//
// Created by Clay Reddick on 1/26/21.
//

#include "TileMapRenderer.h"

void TileMapRenderer::draw() {
    TileRenderer tmp;

    for (auto row : _tileMap->gridData()) {
        for (auto tile : row) {
            tmp = TileRenderer(_window, tile);
            tmp.draw();
        }
    }
}
