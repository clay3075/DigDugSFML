//
// Created by Clay Reddick on 1/30/21.
//

#include "Enemy.h"

const int MOVE_SPEED = 4;

void Enemy::update(sf::Event &event, TileMap &map) {
    move(map);
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
        if (checkForTileCollision(map)) {
            direction++;
            pos = resetPos;
            setPosition(pos);
            moved = false;
        } else {
            moved = true;
        }
    } else {
        direction++;
        moved = false;
    }

}
