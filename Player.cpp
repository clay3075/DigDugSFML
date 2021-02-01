//
// Created by Clay Reddick on 1/30/21.
//

#include "Player.h"

const int MOVE_SPEED = 4;

void Player::update(sf::Event &event, TileMap &map) {
    move(map);
}

void Player::move(TileMap &map) {
    startAnimation();
    auto pos = _sprite.getPosition();

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left)) {
        _sprite.setOrigin({ _sprite.getLocalBounds().width, 0 });
        _sprite.setScale({ -1, 1 });
        pos.x -= MOVE_SPEED;
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right)) {
        _sprite.setOrigin({ 0, 0 });
        _sprite.setScale({ 1, 1 });
        pos.x += MOVE_SPEED;
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up)) {
        pos.y -= MOVE_SPEED;
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down)) {
        pos.y += MOVE_SPEED;
    } else {
        stopAnimation();
    }

    int windowX = _window->getSize().x;
    int windowY = _window->getSize().y;
    int spriteRight;
    int spriteBottom;
    if (_hasAnimation) {
        spriteRight = pos.x + _rectSourceSprite.width;
        spriteBottom = pos.y + _rectSourceSprite.height;
    } else {
        spriteRight = pos.x + _texture.getSize().x * _sprite.getScale().x;
        spriteBottom = pos.y + _texture.getSize().y * _sprite.getScale().y;
    }

    if (pos.x >= 0 && spriteRight <= windowX && pos.y >= 0 && spriteBottom <= windowY)
        _sprite.setPosition(pos);

    Tile* tile = checkForTileCollision(map, 8);
    if (tile) {
        tile->setCollision(false);
        tile->setTexturePath("");
    }
}

