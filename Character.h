//
// Created by Clay Reddick on 1/30/21.
//

#ifndef DIGDUGSFML_CHARACTER_H
#define DIGDUGSFML_CHARACTER_H
#include <SFML/Graphics.hpp>
#include "TileMap.h"
#include <string>

class Character {
public:
    Character(sf::RenderWindow*, std::string);
    bool checkForCollision(sf::Rect<float>&);
    void draw();
    void setScale(float pixelWidth, float pixelHeight);
    void setPosition(sf::Vector2f& pos);
    sf::Vector2f getPosition() { return _sprite.getPosition(); }
    sf::Rect<float> getGlobalBoundingBox() { return _sprite.getGlobalBounds(); }
    virtual void update(sf::Event&, TileMap&) = 0;
    Tile* checkForTileCollision(TileMap& map);
    virtual ~Character() = default;
protected:
    sf::Sprite _sprite;
    sf::Texture _texture;
    sf::RenderWindow* _window;

};


#endif //DIGDUGSFML_CHARACTER_H
