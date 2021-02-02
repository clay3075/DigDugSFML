//
// Created by Clay Reddick on 1/30/21.
//

#include "Enemy.h"

const int MOVE_SPEED = 4;

void Enemy::update(sf::Event &event, TileMap &map) {
    move(map);
    tryToKillTarget();
}

void Enemy::move(TileMap &map) {
    auto pos = _sprite.getPosition();
    auto resetPos = pos;

    switch (direction) {
        case 0:
            pos.x += MOVE_SPEED;
            break;
        case 1:
            pos.x -= MOVE_SPEED;
            break;
        case 2:
            pos.y += MOVE_SPEED;
            break;
        case 3:
            pos.y -= MOVE_SPEED;
            break;
        default:
            direction = 0;
            break;
    }

    int windowX = _window->getSize().x;
    int windowY = _window->getSize().y;
    int spriteRight = pos.x + _texture.getSize().x * _sprite.getScale().x;
    int spriteBottom = pos.y + _texture.getSize().y * _sprite.getScale().y;

    if (pos.x >= 0 && spriteRight <= windowX && pos.y >= 0 && spriteBottom <= windowY) {
        setPosition(pos);
        if (checkForTileCollision(map, 1)) {
            direction = randomDirection();
            pos = resetPos;
            setPosition(pos);
            move(map);
        } else {

        }
    } else {
        direction = randomDirection();
    }
}

void Enemy::tryToKillTarget() {
    if (!_target) return;

    auto targetRect = _target->getGlobalBoundingBox();
    if (checkForCollision(targetRect)) {
        _target->die();
    }
}

int Enemy::randomDirection() {
    std::uniform_int_distribution<int> distribution(0,3);
    return distribution(generator);
}