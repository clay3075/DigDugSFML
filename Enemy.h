//
// Created by Clay Reddick on 1/30/21.
//

#ifndef DIGDUGSFML_ENEMY_H
#define DIGDUGSFML_ENEMY_H
#include <SFML/Graphics.hpp>
#include <utility>
#include "TileMap.h"
#include "Character.h"
#include <random>


class Enemy : public Character {
public:
    Enemy(sf::RenderWindow* window, std::string texturePath) : Character(window, std::move(texturePath)) {};

    void update(sf::Event&, TileMap&) override;
    void setTarget(Character* target) { _target = target; }
private:
    void move(TileMap &map);
    void tryToKillTarget();
    Character* _target = nullptr;
    std::default_random_engine generator;
    int randomDirection();
};


#endif //DIGDUGSFML_ENEMY_H
