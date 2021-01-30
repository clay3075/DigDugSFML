//
// Created by Clay Reddick on 1/26/21.
//

#ifndef SFMLTILEMAP_TILE_H
#define SFMLTILEMAP_TILE_H
#include "Point.h"
#include "Dimensions.h"
#include <string>

class Tile {
public:
    Point getPosition() { return this->position; };
    void setPosition(Point pos) { this->position = pos; }
    Dimensions getDimensions() { return this->dimensions; };
    void setDimensions(Dimensions dim) { this->dimensions = dim; }
    inline int getType() { return this->type; }
    inline void setType(int type) { this->type = type; }
    std::string getTexturePath() { return texturePath; }
    void setTexturePath(std::string path) { texturePath = path; }
    bool getCollision() { return collision; }
    void setCollision(bool collision) { this->collision = collision; }
private:
    Point position = Point(0, 0);
    Dimensions dimensions;
    int type = 0;
    std::string texturePath = "";
    bool collision = false;
};


#endif //SFMLTILEMAP_TILE_H
