#ifndef MAINMENU
#define MAINMENU

#include "GameEngine.h"
#include <iostream>

using std::exception;

class MainMenu {
public:
    MainMenu();
    ~MainMenu();
    void displayMenu();
    void createNewGame();
    void loadSaveGame();
    void printCredits();
    void prompt();
    void quitGame();
    GameEngine* getGameEngine();

private:
    GameEngine* gameEngine;
};

#endif // MAINMENU