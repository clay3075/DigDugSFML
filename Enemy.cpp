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
    startAnimation();

    switch (direction) {
        case Direction::Right:
            pos.x += MOVE_SPEED;
            _sprite.setOrigin({ 0, 0 });
            _sprite.setScale({ 1, 1 });
            break;
        case Direction::Left:
            pos.x -= MOVE_SPEED;
            _sprite.setOrigin({ _sprite.getLocalBounds().width, 0 });
            _sprite.setScale({ -1, 1 });
            break;
        case Direction::Up:
            pos.y += MOVE_SPEED;
            break;
        case Direction::Down:
            pos.y -= MOVE_SPEED;
            break;
        default:
            direction = Direction::Right;
            break;
    }

    int windowX = _window->getSize().x;
    int windowY = _window->getSize().y;
    int spriteRight = pos.x + _texture.getSize().x * _sprite.getScale().x;
    int spriteBottom = pos.y + _texture.getSize().y * _sprite.getScale().y;

    if (pos.x >= 0 && spriteRight <= windowX && pos.y >= 0 && spriteBottom <= windowY) {
        setPosition(pos);
        if (checkForTileCollision(map, 1)) {
            stopAnimation();
            direction = static_cast<Direction>(randomDirection());
            pos = resetPos;
            setPosition(pos);
            move(map);
        }
    } else {
        direction = static_cast<Direction>(randomDirection());
    }
}

void Enemy::tryToKillTarget() {
    if (!_target) return;

    auto targetRect = _target->getGlobalBoundingBox();
    if (checkForCollision(targetRect)) {
        _target->die();
        if (_onKilledTarget) _onKilledTarget(_target, this);
    }
}

int Enemy::randomDirection() {
    std::uniform_int_distribution<int> distribution(0,3);
    return distribution(generator);
}