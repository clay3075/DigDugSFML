#include <SFML/Graphics.hpp>
#include "TileMapRenderer.h"
#include "Player.h"
#include "Enemy.h"
#include <iostream>
#include <vector>

const int FRAME_RATE_LIMIT = 60;
const int SCREEN_WIDTH = 1024;
const int SCREEN_HEIGHT = 768;
const int GAME_PIXEL_SIZE = 64;

const sf::Vector2f PLAYER_START_POS(2*64, 5*64);
const sf::Vector2f ENEMY1_START_POS(11*64, 2*64);
const sf::Vector2f ENEMY2_START_POS(12*64, 7*64);

Enemy* createEnemy(sf::RenderWindow*, Character*, std::string, sf::Vector2f);
void initCharacterGraphics(Character*, sf::Vector2f, bool);
void onPlayerDied(Character*);
void onEnemyDied(Character*);
void cleanUpCharacters(std::vector<Character*> &characters);
void updateCharacters(std::vector<Character*> &characters, sf::Event &event, TileMap &map);
void drawCharacters(std::vector<Character*> &characters);
void reset(sf::RenderWindow*, std::vector<Character*>&, TileMap* map = nullptr);
void playerOnAttack(Player*);
void drawAttack(sf::RenderWindow*);
void attackCooldown();

bool GAME_OVER;
bool attacking;
sf::Texture attackTexture;
sf::Sprite attackSprite;
sf::Clock attackClock;
TileMap map("../map.txt");
Player* player;
std::vector<Character*> characters;

int main()
{
    attackTexture.loadFromFile("../image.png");
    attackSprite.setTexture(attackTexture);
    sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Dig Dug Reimagined");
    window.setFramerateLimit(FRAME_RATE_LIMIT);
    TileMapRenderer mapRenderer(&window, &map);

    reset(&window, characters);

    while (window.isOpen())
    {
        sf::Event event;

        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        if (!GAME_OVER) {
            updateCharacters(characters, event, map);
            attackCooldown();
        } else {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
                reset(&window, characters, &map);
                GAME_OVER = false;
            }
        }

        cleanUpCharacters(characters);

        window.clear();
        mapRenderer.draw();
        drawCharacters(characters);
        drawAttack(&window);
        window.display();
    }

    for (auto character : characters)
        delete character;

    return 0;
}

void initCharacterGraphics(Character* character, sf::Vector2f const startPos, bool setScale = true) {
    if (setScale) character->setScale(GAME_PIXEL_SIZE, GAME_PIXEL_SIZE);
    sf::Vector2f characterStartPos(startPos.x, startPos.y);
    character->setPosition(characterStartPos);
}

Enemy* createEnemy(sf::RenderWindow* window, Character* player, std::string texturePath, sf::Vector2f const startPos) {
    auto enemy = new Enemy(window, "../DigDugMonster.png");
    initCharacterGraphics(enemy, startPos, false);
    enemy->setCanAnimate(true);
    enemy->setSpriteSheetFrameDimensions(GAME_PIXEL_SIZE, GAME_PIXEL_SIZE, 3, 12);
    enemy->setTarget(player);
    enemy->setOnDie(onEnemyDied);
    return enemy;
}

void onPlayerDied(Character* player) {
    GAME_OVER = true;
    for (auto character : characters) {
        character->setCanAnimate(false);
    }
//    player->stopAnimation();
}

void onEnemyDied(Character* enemy) {
    enemy->markForDestruction();
}

void cleanUpCharacters(std::vector<Character*> &characters) {
    for (int i = 0; i < characters.size(); i++) {
        if (characters[i]->isMarkedForDestruction()) {
            auto tmp = characters[i];
            characters.erase(characters.begin() + i);
            delete tmp;
        }
    }
}

void reset(sf::RenderWindow* window, std::vector<Character*>& characters, TileMap* map) {
    player = new Player(window, "../DigDugCharacter.png");
    player->setCanAnimate(true);
    player->setSpriteSheetFrameDimensions(GAME_PIXEL_SIZE, GAME_PIXEL_SIZE, 3, 12);
    player->setOnDie(onPlayerDied);
    player->setOnAttack(playerOnAttack);
    initCharacterGraphics(player, PLAYER_START_POS, false);

    Enemy* enemy1 = createEnemy(window, player, "../image.png", ENEMY1_START_POS);
    Enemy* enemy2 = createEnemy(window, player, "../image.png", ENEMY2_START_POS);

    std::vector<Character*> tmpCharacters = {player, enemy1, enemy2};

    for(auto character : characters) {
        delete character;
    }
    characters.clear();
    characters.assign(tmpCharacters.begin(), tmpCharacters.end());
    if (map) map->reset();
}

void updateCharacters(std::vector<Character*> &characters, sf::Event &event, TileMap &map) {
    for (auto character : characters) {
        if (character) {
            character->update(event, map);
        }
    }
}

void drawCharacters(std::vector<Character*> &characters) {
    for (auto character : characters) {
        if (character) {
            character->draw();
        }
    }
}

void playerOnAttack(Player* player) {
    auto playerRect = player->getGlobalBoundingBox();

    int width = player->getDirection() == Direction::Right ? playerRect.width : -playerRect.width;
    attacking = !map.checkForCollision(playerRect.left + width, playerRect.top, playerRect.width, playerRect.height, 8);
    if (player->canAttack() && attacking) {
        attackSprite.setPosition(playerRect.left + width, playerRect.top);
        double textureWidth = attackSprite.getTexture()->getSize().x;
        double textureHeight = attackSprite.getTexture()->getSize().y;
        attackSprite.setScale(GAME_PIXEL_SIZE / textureWidth, GAME_PIXEL_SIZE / textureHeight);
        player->setCanMove(false);
        player->setCanAttack(false);
        attackClock.restart();
    };
}

void drawAttack(sf::RenderWindow* window) {
    if (attacking) window->draw(attackSprite);
}

void attackCooldown() {
    if (attackClock.getElapsedTime().asMilliseconds() > 1000) {
        attacking = false;
        player->setCanAttack(true);
        player->setCanMove(true);
    }
}