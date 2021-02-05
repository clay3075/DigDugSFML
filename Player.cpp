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
        _sprite.setOrigin({ _sprite.getLocalBounds().width, 0 });
        _sprite.setScale({ -1, 1 });
        _sprite.setRotation(0);
        pos.x -= MOVE_SPEED;
        direction = Direction::Left;
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right)) {
        _sprite.setOrigin({ 0, 0 });
        _sprite.setScale({ 1, 1 });
        _sprite.setRotation(0);
        direction = Direction::Right;
        pos.x += MOVE_SPEED;
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up)) {
        _sprite.setOrigin({ _sprite.getLocalBounds().width, _sprite.getLocalBounds().height-64 });
        _sprite.setScale({ 1, 1 });
        _sprite.setRotation(-90);
        pos.y -= MOVE_SPEED;
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down)) {
        _sprite.setOrigin({ _sprite.getLocalBounds().width-64, _sprite.getLocalBounds().height });
        _sprite.setScale({ 1, 1 });
        _sprite.setRotation(90);
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

    int width = this->getDirection() == Direction::Right ? playerRect.width : -playerRect.width;
    _attacking = !map.checkForCollision(playerRect.left + width, playerRect.top, playerRect.width, playerRect.height, 8);
    if (this->canAttack() && _attacking) {
        _attackSprite.setPosition(playerRect.left + width, playerRect.top);
        if (direction == Direction::Left) {
            _attackSprite.setOrigin({ _attackSprite.getLocalBounds().width, 0 });
            _attackSprite.setScale({ -1, 1 });
        } else if (direction == Direction::Right) {
            _attackSprite.setOrigin({ 0, 0 });
            _attackSprite.setScale({ 1, 1 });
        } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up)) {
            _attackSprite.setOrigin({ _attackSprite.getLocalBounds().width, _attackSprite.getLocalBounds().height-64 });
            _attackSprite.setScale({ 1, 1 });
            _attackSprite.setRotation(-90);
        } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down)) {
            _attackSprite.setOrigin({ _attackSprite.getLocalBounds().width-64, _attackSprite.getLocalBounds().height });
            _attackSprite.setScale({ 1, 1 });
            _attackSprite.setRotation(90);
        }
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

