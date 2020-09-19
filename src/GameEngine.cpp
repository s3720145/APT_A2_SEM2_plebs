#include "GameEngine.h"

GameEngine::GameEngine() {
    gameboard = new Gameboard();
    inputProcessing = new InputProcessing();
    outputProcessing = new OutputProcessing();
}

GameEngine::~GameEngine() {

}

void GameEngine::newGame() {
    std::cout << "hello";
}

void GameEngine::loadGame() {

}

void GameEngine::saveGame() {

}

void GameEngine::newRound() {

}

const Gameboard* GameEngine::getGameboard() {
    return this->gameboard;
}

