//
// Created by Clay Reddick on 2/4/21.
//

#ifndef DIGDUGSFML_DRAGON_H
#define DIGDUGSFML_DRAGON_H
#include <SFML/Graphics.hpp>
#include "Enemy.h"

class Dragon: public Enemy {
public:
    explicit Dragon(sf::RenderWindow* window, Dimensions screen) : Enemy(window, "../DigDugMonster.png", screen) {
        this->setCanAnimate(true);
        this->setSpriteSheetFrameDimensions(64, 64, 3, 12);
    }
};

#endif //DIGDUGSFML_DRAGON_H
