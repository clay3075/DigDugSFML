//
// Created by Clay Reddick on 1/26/21.
//

#ifndef SFMLTILEMAP_TILEMAP_H
#define SFMLTILEMAP_TILEMAP_H
#include "Tile.h"
#include "Dimensions.h"
#include <vector>
#include <string>
#include <map>

class TileMap {
public:
    TileMap() = default;
    explicit TileMap(std::string tileMapFilePath);
    ~TileMap() = default;
    void printGrid();
    Dimensions getTileDimension() { return this->tileDimensions; };
    std::vector<std::vector<Tile*>> gridData() {return grid; }
    std::string getTexturePath(int type) { return texturePaths.at(type); }
    Tile* checkForCollision(float x, float y);
    Tile* checkForCollision(float left, float top, float width, float height, float boxBuffer);
    void reset();
private:
    //properties
    std::vector<std::vector<Tile*>> grid;
    Dimensions tileDimensions{};
    std::map<int, std::string> texturePaths;
    std::map<int, bool> textureCollisions;
    std::string _tileMapFilePath;
    //methods
    void initGrid(std::string path);
};


#endif //SFMLTILEMAP_TILEMAP_H
