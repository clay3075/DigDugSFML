//
// Created by Clay Reddick on 1/30/21.
//

#include "Character.h"
#include <iostream>

Character::Character(sf::RenderWindow* window, std::string texturePath) {
    _window = window;

    if (!_texture.loadFromFile(texturePath)) {
        std::cout << "Error loading character texture" << std::endl;
    }
    _sprite.setTexture(_texture);
}

bool Character::checkForCollision(sf::Rect<float> &position) {
    auto spriteBounds = _sprite.getGlobalBounds();

    return spriteBounds.intersects(position);
}

Tile* Character::checkForTileCollision(TileMap &map) {
    auto playerBoundingBox = this->getGlobalBoundingBox();
    return map.checkForCollision(playerBoundingBox.left, playerBoundingBox.top, playerBoundingBox.width,
                                       playerBoundingBox.height, 8);

}

void Character::draw() {
    _window->draw(_sprite);
}

void Character::setScale(float pixelWidth, float pixelHeight) {
    double textureWidth = _sprite.getTexture()->getSize().x;
    double textureHeight = _sprite.getTexture()->getSize().y;
    _sprite.setScale(pixelWidth/textureWidth, pixelHeight/textureHeight);
}

void Character::setPosition(sf::Vector2f &pos) {
    _sprite.setPosition(pos);
}


