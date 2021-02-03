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
    void setOnAttack(void (* attack)(Player*)) { _attack = attack; }
    void setCanMove(bool canMove) {
        _canMove = canMove;
        if (!_canMove) stopAnimation();
    }
    void setCanAttack(bool canAttack) { _canAttack = canAttack; }
    bool canAttack() { return _canAttack; }
private:
    void move(TileMap &map);
    void (* _attack)(Player*) = nullptr;
    bool _canMove = true;
    bool _canAttack = true;
};


#endif //DIGDUGSFML_PLAYER_H
