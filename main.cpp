#include <SFML/Graphics.hpp>
#include "TileMapRenderer.h"
#include "Player.h"
#include "Enemy.h"
#include <iostream>

const int FRAME_RATE_LIMIT = 60;
const int SCREEN_WIDTH = 1024;
const int SCREEN_HEIGHT = 768;
const int GAME_PIXEL_SIZE = 64;

const sf::Vector2f PLAYER_START_POS(2*64, 5*64);
const sf::Vector2f ENEMY1_START_POS(11*64, 2*64);
const sf::Vector2f ENEMY2_START_POS(12*64, 7*64);

int main()
{
    TileMap map("../map.txt");

    sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "SFML Application");
    window.setFramerateLimit(FRAME_RATE_LIMIT);
    TileMapRenderer mapRenderer(&window, &map);

    Character* player = new Player(&window, "../image.png");
    player->setScale(GAME_PIXEL_SIZE, GAME_PIXEL_SIZE);
    sf::Vector2f playerStartPos(PLAYER_START_POS.x, PLAYER_START_POS.y);
    player->setPosition(playerStartPos);

    Character* enemy1 = new Enemy(&window, "../image.png");
    enemy1->setScale(GAME_PIXEL_SIZE, GAME_PIXEL_SIZE);
    sf::Vector2f enemyStartPos(ENEMY1_START_POS.x, ENEMY1_START_POS.y);
    enemy1->setPosition(enemyStartPos);

    Character* enemy2 = new Enemy(&window, "../image.png");
    enemy2->setScale(GAME_PIXEL_SIZE, GAME_PIXEL_SIZE);
    sf::Vector2f enemy2StartPos(ENEMY2_START_POS.x, ENEMY2_START_POS.y);
    enemy2->setPosition(enemy2StartPos);

    while (window.isOpen())
    {
        sf::Event event;

        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        player->update(event, map);
        enemy1->update(event, map);
        enemy2->update(event, map);

        window.clear();
        mapRenderer.draw();
        player->draw();
        enemy1->draw();
        enemy2->draw();
        window.display();
    }

    delete player;

    return 0;
}