//
// Created by Clay Reddick on 1/30/21.
//

#include "Player.h"

const int MOVE_SPEED = 4;

Player::Player(sf::RenderWindow *window) : Character(window, "../DigDugCharacter.png") {
    {
        setCanAnimate(true);
        setSpriteSheetFrameDimensions(64, 64, 3, 12);

        _attackTexture = _texture;
        sf::IntRect rect(4*64, 0, 64, 64);
        _attackSprite.setTexture(_attackTexture);
        _attackSprite.setTextureRect(rect);
    };
}

void Player::update(sf::Event &event, TileMap &map) {
    attackCooldown();
    if (_canMove) move(map);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) attack(map);
}

void Player::move(TileMap &map) {
    startAnimation();
    auto pos = _sprite.getPosition();

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left)) {
        pos.x -= MOVE_SPEED;
        direction = Direction::Left;
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right)) {
        direction = Direction::Right;
        pos.x += MOVE_SPEED;
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up)) {
        direction = Direction::Up;
        pos.y -= MOVE_SPEED;
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down)) {
        direction = Direction::Down;
        pos.y += MOVE_SPEED;
    } else {
        stopAnimation();
    }
    rotateSpriteBasedOnInput(_sprite);

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

    if (_canMove && pos.x >= 0 && spriteRight <= windowX && pos.y >= 0 && spriteBottom <= windowY)
        _sprite.setPosition(pos);

    Tile* tile = checkForTileCollision(map, 8);
    if (tile) {
        tile->setCollision(false);
        tile->setTexturePath("");
    }
}

void Player::attack(TileMap &map) {
    auto playerRect = this->getGlobalBoundingBox();

    if (this->getDirection() == Direction::Left || this->getDirection() == Direction::Right) {
        int width = this->getDirection() == Direction::Right ? playerRect.width : -playerRect.width;
        _attacking = !map.checkForCollision(playerRect.left + width, playerRect.top, playerRect.width, playerRect.height, 8);
        if (this->canAttack() && _attacking) _attackSprite.setPosition(playerRect.left + width, playerRect.top);
    }

    if (this->getDirection() == Direction::Up || this->getDirection() == Direction::Down) {
        int height = this->getDirection() == Direction::Up ? -playerRect.height : playerRect.height;
        _attacking = !map.checkForCollision(playerRect.left, playerRect.top + height, playerRect.width, playerRect.height, 8);
        if (this->canAttack() && _attacking)  _attackSprite.setPosition(playerRect.left, playerRect.top + height);
    }

    if (this->canAttack() && _attacking) {
        rotateSpriteBasedOnInput(_attackSprite);
        this->setCanMove(false);
        this->setCanAttack(false);
        this->_rectSourceSprite.left = 3*64;
        this->_sprite.setTextureRect(this->_rectSourceSprite);
        _attackClock.restart();
        if(_onAttack) _onAttack(this);
    }
}

void Player::attackCooldown() {
    if (_attackClock.getElapsedTime().asMilliseconds() > 1000) {
        _attacking = false;
        setCanAttack(true);
        setCanMove(true);
        this->_rectSourceSprite.left = 0;
        this->_sprite.setTextureRect(this->_rectSourceSprite);
    }
}

void Player::draw() {
    Character::draw();
    if (_attacking) _window->draw(_attackSprite);
}

void Player::rotateSpriteBasedOnInput(sf::Sprite &sprite) {
    switch (direction) {
        case Direction::Left:
            sprite.setOrigin({ sprite.getLocalBounds().width, 0 });
            sprite.setScale({ -1, 1 });
            sprite.setRotation(0);
            break;
        case Direction::Right:
            sprite.setOrigin({ 0, 0 });
            sprite.setScale({ 1, 1 });
            sprite.setRotation(0);
            break;
        case Direction::Up:
            sprite.setOrigin({ sprite.getLocalBounds().width, sprite.getLocalBounds().height-64 });
            sprite.setScale({ 1, 1 });
            sprite.setRotation(-90);
            break;
        case Direction::Down:
            sprite.setOrigin({ sprite.getLocalBounds().width-64, sprite.getLocalBounds().height-64 });
            sprite.setScale({ -1, 1 });
            sprite.setRotation(-90);
            break;
    }
}

