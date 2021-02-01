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

Tile* Character::checkForTileCollision(TileMap &map, float collisionBoxBufferInPixels) {
    auto playerBoundingBox = this->getGlobalBoundingBox();
    return map.checkForCollision(playerBoundingBox.left, playerBoundingBox.top, playerBoundingBox.width,
                                       playerBoundingBox.height, collisionBoxBufferInPixels);

}

void Character::draw() {
    animate();
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

void Character::die() {
    if (_onDie)
        _onDie(this);
}

void Character::animate() {
 if (_hasAnimation) {
     if (_clock.getElapsedTime().asSeconds() > 1/_fps){
         if (_rectSourceSprite.left == _frames*_rectSourceSprite.width)
             _rectSourceSprite.left = 0;
         else
             _rectSourceSprite.left += _rectSourceSprite.width;
         _sprite.setTextureRect(_rectSourceSprite);
         _clock.restart();
     }
 }
}

void Character::setSpriteSheetFrameDimensions(int width, int height, int frames, float fps) {
    _frames = frames - 1;
    _fps = fps;
    _rectSourceSprite.height = height;
    _rectSourceSprite.width = width;
    _sprite.setTextureRect(_rectSourceSprite);
}


