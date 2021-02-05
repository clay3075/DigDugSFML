//
// Created by Clay Reddick on 1/30/21.
//

#ifndef DIGDUGSFML_PLAYER_H
#define DIGDUGSFML_PLAYER_H
#include <utility>

#include "Character.h"

class Player : public Character {
public:
    explicit Player(sf::RenderWindow* window);

    void update(sf::Event&, TileMap&) override;
    void setOnAttack(void (* attack)(Player*)) { _onAttack = attack; }
    void setCanMove(bool canMove) {
        _canMove = canMove;
        if (!_canMove) stopAnimation();
    }
    void setCanAttack(bool canAttack) { _canAttack = canAttack; }
    bool canAttack() { return _canAttack; }
private:
    void move(TileMap &map);
    void attack(TileMap &map);
    void (* _onAttack)(Player*) = nullptr;
    void attackCooldown();
    bool _canMove = true;
    bool _canAttack = true;
    sf::Texture _attackTexture;
    sf::Sprite _attackSprite;
    sf::Clock _attackClock;
    bool _attacking = false;
    void draw() override;
    void rotateSpriteBasedOnInput(sf::Sprite&);
};


#endif //DIGDUGSFML_PLAYER_H
