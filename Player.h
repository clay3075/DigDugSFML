//
// Created by Clay Reddick on 1/30/21.
//

#ifndef DIGDUGSFML_PLAYER_H
#define DIGDUGSFML_PLAYER_H
#include "Character.h"

class Player : public Character {
public:
    Player(sf::RenderWindow* window, std::string texturePath) : Character(window, texturePath) {};

    void update(sf::Event&);

private:
    void move();
};


#endif //DIGDUGSFML_PLAYER_H
