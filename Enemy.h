//
// Created by Clay Reddick on 1/30/21.
//

#ifndef DIGDUGSFML_ENEMY_H
#define DIGDUGSFML_ENEMY_H
#include <SFML/Graphics.hpp>
#include "TileMap.h"
#include "Character.h"


class Enemy : public Character {
public:
    Enemy(sf::RenderWindow* window, std::string texturePath) : Character(window, texturePath) {};

    void update(sf::Event&, TileMap&);
private:
    void move(TileMap &map);
    int direction = 0;
    bool moved = false;
};


#endif //DIGDUGSFML_ENEMY_H
