#ifndef MAINMENU
#define MAINMENU

#include "GameEngine.h"

class MainMenu {
public:
    MainMenu();
    ~MainMenu();
    void displayMenu();
    void createNewGame();
    void loadSaveGame();
    void testingMode();
    void printCredits();
    void quitGame();

private:
    
};

#endif // MAINMENU