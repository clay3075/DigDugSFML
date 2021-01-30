#include <SFML/Graphics.hpp>
#include "TileMapRenderer.h"
#include "Player.h"
#include <iostream>

const int FRAME_RATE_LIMIT = 60;
const int SCREEN_WIDTH = 1024;
const int SCREEN_HEIGHT = 768;
const int GAME_PIXEL_SIZE = 64;

const sf::Vector2f PLAYER_START_POS(2*64, 5*64);

void checkForTileCollision(Character& player, TileMap& map);

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

    while (window.isOpen())
    {
        sf::Event event;

        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        player->update(event);
        checkForTileCollision(*player, map);

        window.clear();
        mapRenderer.draw();
        player->draw();
        window.display();
    }

    delete player;

    return 0;
}

void checkForTileCollision(Character& player, TileMap& map) {
    auto playerBoundingBox= player.getGlobalBoundingBox();
    Tile* tile = map.checkForCollision(playerBoundingBox.left, playerBoundingBox.top, playerBoundingBox.width, playerBoundingBox.height, 8);
    if (tile) {
        tile->setCollision(false);
        tile->setTexturePath("");
        std::cout << tile->getPosition().x << " " << tile->getPosition().y << std::endl << tile->getTexturePath();
    }
}