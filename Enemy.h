//
// Created by Clay Reddick on 1/30/21.
//

#ifndef DIGDUGSFML_ENEMY_H
#define DIGDUGSFML_ENEMY_H
#include <SFML/Graphics.hpp>
#include <utility>
#include "TileMap.h"
#include "Character.h"


class Enemy : public Character {
public:
    Enemy(sf::RenderWindow* window, std::string texturePath) : Character(window, std::move(texturePath)) {};

    void update(sf::Event&, TileMap&) override;
    void setTarget(Character* target) { _target = target; }
private:
    void move(TileMap &map);
    void tryToKillTarget();
    int direction = 0;
    bool moved = false;
    Character* _target = nullptr;
};


#endif //DIGDUGSFML_ENEMY_H
