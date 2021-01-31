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
void initCharacterGraphics(Character*, sf::Vector2f);
void onPlayerDied(Character*);
void onEnemyDied(Character*);
void cleanUpCharacters(std::vector<Character*> &characters);
void reset(sf::RenderWindow*, std::vector<Character*>&, TileMap* map = nullptr);

bool GAME_OVER;

int main()
{
    TileMap map("../map.txt");

    sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "SFML Application");
    window.setFramerateLimit(FRAME_RATE_LIMIT);
    TileMapRenderer mapRenderer(&window, &map);

    std::vector<Character*> characters;
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
            for (auto character : characters) {
                if (character) {
                    character->update(event, map);
                }
            }
        } else {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
                reset(&window, characters, &map);
                GAME_OVER = false;
            }
        }

        cleanUpCharacters(characters);

        window.clear();
        mapRenderer.draw();
        for (auto character : characters) {
            if (character) {
                character->draw();
            }
        }
        window.display();
    }

    for (auto character : characters)
        delete character;

    return 0;
}

void initCharacterGraphics(Character* character, sf::Vector2f const startPos) {
    character->setScale(GAME_PIXEL_SIZE, GAME_PIXEL_SIZE);
    sf::Vector2f characterStartPos(startPos.x, startPos.y);
    character->setPosition(characterStartPos);
}

Enemy* createEnemy(sf::RenderWindow* window, Character* player, std::string texturePath, sf::Vector2f const startPos) {
    auto enemy = new Enemy(window, "../image.png");
    initCharacterGraphics(enemy, startPos);
    enemy->setTarget(player);
    enemy->setOnDie(onEnemyDied);
    return enemy;
}

void onPlayerDied(Character*) {
    GAME_OVER = true;
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
    Character* player = new Player(window, "../image.png");
    player->setOnDie(onPlayerDied);
    initCharacterGraphics(player, PLAYER_START_POS);

    Character* enemy1 = createEnemy(window, player, "../image.png", ENEMY1_START_POS);
    Character* enemy2 = createEnemy(window, player, "../image.png", ENEMY2_START_POS);

    std::vector<Character*> tmpCharacters = {player, enemy1, enemy2};

    characters.clear();
    characters.assign(tmpCharacters.begin(), tmpCharacters.end());
    if (map) map->reset();
}