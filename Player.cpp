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

    _sprite.setPosition(pos);
}
