//
// Created by Clay Reddick on 2/6/21.
//

#ifndef DIGDUGSFML_UIMANAGER_H
#define DIGDUGSFML_UIMANAGER_H
#include <SFML/Graphics.hpp>
#include "Dimensions.h"

class UIManager {
public:
    UIManager(sf::RenderWindow*, Dimensions screen);
    void drawScore(int score, float percentageLeft, float percentageTop, int fontSize);
    void drawGameOver(bool playerWon, float percentageLeft, float percentageTop, int fontSize);
    void drawScore(int score, int left, int top, int fontSize);
    void drawGameOver(bool playerWon, int left, int top, int fontSize);
private:
    sf::RenderWindow* _window;
    sf::Text _score;
    sf::Text _gameOver;
    sf::Text _playerWon;
    sf::Text _restart;
    sf::Color _textColor = sf::Color::White;
    sf::Font _font;
    Dimensions _screenDimensions;

    void initText(sf::Text&);
};


#endif //DIGDUGSFML_UIMANAGER_H
