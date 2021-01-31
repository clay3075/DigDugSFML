//
// Created by Clay Reddick on 1/30/21.
//

#ifndef DIGDUGSFML_PLAYER_H
#define DIGDUGSFML_PLAYER_H
#include <utility>

#include "Character.h"

class Player : public Character {
public:
    Player(sf::RenderWindow* window, std::string texturePath) : Character(window, std::move(texturePath)) {};

    void update(sf::Event&, TileMap&) override;
private:
    void move(TileMap &map);
};


#endif //DIGDUGSFML_PLAYER_H
