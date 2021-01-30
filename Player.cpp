//
// Created by Clay Reddick on 1/30/21.
//

#include "Player.h"
#include <iostream>

const int MOVE_SPEED = 4;

void Player::update(sf::Event &event) {
    move();
}

void Player::move() {
    auto pos = _sprite.getPosition();

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left)) {
        pos.x -= MOVE_SPEED;
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right)) {
        pos.x += MOVE_SPEED;
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up)) {
        pos.y -= MOVE_SPEED;
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down)) {
        pos.y += MOVE_SPEED;
    }

    int windowX = _window->getSize().x;
    int windowY = _window->getSize().y;
    int spriteRight = pos.x + _texture.getSize().x * _sprite.getScale().x;
    int spriteBottom = pos.y + _texture.getSize().y * _sprite.getScale().y;

    if (pos.x >= 0 && spriteRight <= windowX && pos.y >= 0 && spriteBottom <= windowY)
        _sprite.setPosition(pos);
}
