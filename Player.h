//
// Created by Clay Reddick on 1/30/21.
//

#ifndef DIGDUGSFML_PLAYER_H
#define DIGDUGSFML_PLAYER_H
#include <utility>

#include "Character.h"
#include "Enemy.h"

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
    void setEnemies(std::vector<Enemy*> enemies) { _enemies = enemies; }
private:
    // methods
    void move(TileMap &map);
    void attack(TileMap &map);
    void attackCooldown();
    void draw() override;
    void rotateSpriteBasedOnInput(sf::Sprite&);
    void interpolate(sf::Vector2<float>&);
    // properties
    bool _canMove = true;
    bool _canAttack = true;
    bool _attacking = false;
    sf::Texture _attackTexture;
    sf::Sprite _attackSprite;
    sf::Clock _attackClock;
    void (* _onAttack)(Player*) = nullptr;
    std::vector<Enemy*> _enemies;
};


#endif //DIGDUGSFML_PLAYER_H
