#include <SFML/Graphics.hpp>
#include "TileMapRenderer.h"
#include "Player.h"
#include "Enemy.h"
#include "Dragon.h"
#include "UIManager.h"
#include <iostream>
#include <vector>

const int FRAME_RATE_LIMIT = 60;
const int SCREEN_WIDTH = 1024;
const int SCREEN_HEIGHT = 768;

const sf::Vector2f PLAYER_START_POS(2*64, 5*64);
const sf::Vector2f ENEMY1_START_POS(11*64, 2*64);
const sf::Vector2f ENEMY2_START_POS(12*64, 7*64);

Enemy* createEnemy(sf::RenderWindow*, Character*, sf::Vector2f);
void onPlayerDied(Character*);
void onEnemyDied(Character*);
void cleanUpCharacters(std::vector<Character*> &characters);
void updateCharacters(std::vector<Character*> &characters, sf::Event &event, TileMap &map);
void drawCharacters(std::vector<Character*> &characters);
void reset(sf::RenderWindow*, std::vector<Character*>&, TileMap* map = nullptr);

bool GAME_OVER;
int enemiesKilled = 0;
int numberOfEnemies = 0;
std::vector<Character*> characters;

int main()
{
    TileMap map("../map.txt");
    sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Dig Dug Reimagined");
    window.setFramerateLimit(FRAME_RATE_LIMIT);
    TileMapRenderer mapRenderer(&window, &map);
    Dimensions screenDim(SCREEN_WIDTH, SCREEN_HEIGHT);
    UIManager uiManager(&window, screenDim);

    reset(&window, characters);

    while (window.isOpen())
    {
        sf::Event event{};

        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        if (!GAME_OVER) {
            updateCharacters(characters, event, map);
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
        uiManager.drawScore(enemiesKilled, .025f, .025f, 25);
        if(GAME_OVER) uiManager.drawGameOver(numberOfEnemies == enemiesKilled, .39f, .40f, 50);
        window.display();
    }

    for (auto character : characters)
        delete character;

    return 0;
}

Enemy* createEnemy(sf::RenderWindow* window, Character* player, sf::Vector2f const startPos) {
    auto enemy = new Dragon(window);

    enemy->setTarget(player);
    enemy->setOnDie(onEnemyDied);
    enemy->setPosition(const_cast<sf::Vector2f &>(startPos));
    return enemy;
}

void onPlayerDied(Character* player) {
    GAME_OVER = true;
    for (auto character : characters) {
        character->setCanAnimate(false);
    }
}

void onEnemyDied(Character* enemy) {
    enemiesKilled++;
    if (numberOfEnemies == enemiesKilled) {
        GAME_OVER = true;
    }
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
    Player* player = new Player(window);

    player->setOnDie(onPlayerDied);
    player->setPosition(const_cast<sf::Vector2f &>(PLAYER_START_POS));

    Enemy* enemy1 = createEnemy(window, player, ENEMY1_START_POS);
    Enemy* enemy2 = createEnemy(window, player, ENEMY2_START_POS);
    numberOfEnemies = 2;

    std::vector<Character*> tmpCharacters = {player, enemy1, enemy2};
    player->setEnemies({enemy1, enemy2});

    for(auto character : characters) {
        delete character;
    }
    characters.clear();
    characters.assign(tmpCharacters.begin(), tmpCharacters.end());
    if (map) map->reset();
    enemiesKilled = 0;
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