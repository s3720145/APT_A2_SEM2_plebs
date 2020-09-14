#include "MainMenu.h"
#include <iostream>

using std::exception;

MainMenu::MainMenu() {

}

MainMenu::~MainMenu() {

}

void MainMenu::displayMenu() {
    std::cout << "hello world";

}

void MainMenu::createNewGame() {

}

void MainMenu::loadSaveGame() {

}

void MainMenu::testingMode() {

}

void MainMenu::printCredits() {

}

void MainMenu::quitGame() {
    throw exception();
}