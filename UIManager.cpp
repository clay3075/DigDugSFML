//
// Created by Clay Reddick on 2/6/21.
//

#include "UIManager.h"
#include <string>
#include <iostream>

UIManager::UIManager(sf::RenderWindow* window, Dimensions screen) {
    _window = window;
    _font.loadFromFile("../ARCADECLASSIC.TTF");
    initText(_gameOver);
    initText(_playerWon);
    initText(_restart);
    initText(_score);
    _screenDimensions = screen;
}

void UIManager::drawScore(int score, float percentageLeft, float percentageTop, int fontSize) {
    drawScore(score, (int)(_screenDimensions.width * percentageLeft), (int)(_screenDimensions.height * percentageTop), fontSize);
}

void UIManager::drawGameOver(bool playerWon, float percentageLeft, float percentageTop, int fontSize) {
    drawGameOver(playerWon, (int)(_screenDimensions.width * percentageLeft), (int)(_screenDimensions.height * percentageTop), fontSize);
}

void UIManager::initText(sf::Text & text) {
    text.setFillColor(_textColor);
    text.setFont(_font);
}

void UIManager::drawScore(int score, int left, int top, int fontSize) {
    _score.setString("Score\t " + std::to_string(score));
    _score.setPosition(left, top);
    _score.setCharacterSize(fontSize);
    _window->draw(_score);
}

void UIManager::drawGameOver(bool playerWon, int left, int top, int fontSize) {
    float offset;

    _gameOver.setString("GAME\tOVER");
    _gameOver.setPosition(left, top);
    _gameOver.setCharacterSize(fontSize);
    _window->draw(_gameOver);

    int playerWonFontSize = fontSize * .75f;
    _playerWon.setString(playerWon ? "You\tWon" : "You\tLost");
    offset = ((_gameOver.getString().getSize() * fontSize) / 2.0 - (_playerWon.getString().getSize() * playerWonFontSize) / 2.0);
    _playerWon.setPosition(left + offset/2, top + fontSize);
    _playerWon.setCharacterSize(playerWonFontSize);
    _window->draw(_playerWon);

    int restartFontSize = playerWonFontSize * .75f;
    _restart.setString("Press\tENTER\tto\trestart");
    offset = ((_gameOver.getString().getSize() * fontSize) / 2.0 - (_restart.getString().getSize() * restartFontSize) / 2.0);
    _restart.setPosition(left + offset/2, top + fontSize + playerWonFontSize);
    _restart.setCharacterSize(restartFontSize);
    _window->draw(_restart);
}


