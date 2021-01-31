//
// Created by Clay Reddick on 1/26/21.
//

#include <iostream>
#include "TileRenderer.h"

void TileRenderer::draw() {
    sf::Sprite sprite;
    Dimensions tileDim = _tile->getDimensions();
    Point tilePos = _tile->getPosition();
    float spriteX = tilePos.x * tileDim.width;
    float spriteY = tilePos.y * tileDim.height;

    auto texture = getTexture(_tile->getTexturePath());

    sprite.setTexture(texture);
    sprite.setPosition(spriteX, spriteY);
    double textureWidth = texture.getSize().x;
    double textureHeight = texture.getSize().y;
    sprite.setScale(tileDim.width/textureWidth, tileDim.height/textureHeight);
    _window->draw(sprite);
}

sf::Texture TileRenderer::getTexture(std::string id) {
    sf::Texture texture;

    auto textureIterator = textures.find(id);
    if (textureIterator != textures.end()) {
        texture = textureIterator->second;
    } else {
        if (id != "" && !texture.loadFromFile(id))
        {
            std::cout << "Failed to load texture";
        } else {
            textures.insert(std::pair<std::string, sf::Texture>(id, texture));
        }
    }

    return texture;
}

std::map<std::string, sf::Texture> TileRenderer::textures;