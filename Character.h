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
    void animate();
    void setCanAnimate(bool canAnimate) { _hasAnimation = canAnimate; }
    void setSpriteSheetFrameDimensions(int width, int height, int frames, float fps);
    void setScale(float pixelWidth, float pixelHeight);
    void setPosition(sf::Vector2f& pos);
    sf::Vector2f getPosition() { return _sprite.getPosition(); }
    sf::Rect<float> getGlobalBoundingBox() { return _sprite.getGlobalBounds(); }
    virtual void update(sf::Event&, TileMap&) = 0;
    Tile* checkForTileCollision(TileMap& map, float collisionBoxBufferInPixels);
    virtual ~Character() = default;
    void die();
    void setOnDie(void (*onDie)(Character*)) { _onDie = onDie; }
    void markForDestruction() { _readyToDestroy = true; }
    bool isMarkedForDestruction() { return _readyToDestroy; }
    void startAnimation() { _isAnimating = true; }
    void stopAnimation() {
        _isAnimating = false;
        _rectSourceSprite.left = 0;
        _sprite.setTextureRect(_rectSourceSprite);
    }
protected:
    sf::Sprite _sprite;
    sf::Texture _texture;
    sf::RenderWindow* _window;
    void (*_onDie)(Character*) = nullptr;
    bool _readyToDestroy;
    int _frames = 0;
    float _fps = 0.0f;
    sf::IntRect _rectSourceSprite;
    bool _hasAnimation;
    bool _isAnimating;
    sf::Clock _clock;
};


#endif //DIGDUGSFML_CHARACTER_H
