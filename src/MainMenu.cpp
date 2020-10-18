#include "MainMenu.h"

MainMenu::MainMenu() {
    gameEngine = new GameEngine();
}

MainMenu::~MainMenu() {

}

void MainMenu::displayMenu() {
    std::cout << std::endl;
    std::cout << "Menu" << std::endl;
    std::cout << "----" << std::endl;
    std::cout << "1. New Game" << std::endl;
    std::cout << "2. Load Game" << std::endl;
    std::cout << "3. Credits (Show student information)" << std::endl;
    std::cout << "4. Quit" << std::endl;

    prompt();
}

void MainMenu::prompt() {
    std::string input;
    std::cout << std::endl << "> ";
    std::cin >> input;
    
    if(std::cin.eof() == true){
        std::cout << std::endl;
        quitGame();
    } else if(input == "1") {
        createNewGame();
    } else if(input == "2") {
        loadSaveGame();
    } else if(input == "3") {
        printCredits();
    } else if(input == "4") {
        quitGame();
    } else {
        std::cout << "Invalid Input";
        prompt();
    }
}

void MainMenu::createNewGame() {
    std::string input;
    int mode = 0;
    std::cout << std::endl;
    std::cout << "Game Mode" << std::endl;
    std::cout << "----" << std::endl;
    std::cout << "1. Normal Game" << std::endl;
    std::cout << "2. Grey Board" << std::endl;
    std::cout << "3. Six Tiles" << std::endl;
    std::cout << "4. Quit" << std::endl;
    std::cout << std::endl << "> ";
    std::cin >> input;
    if(std::cin.eof() == true){
        std::cout << std::endl;
        quitGame();
    } else if(input == "1") {
        mode = 0;
    } else if(input == "2") {
        mode = 1;
    } else if(input == "3") {
        mode = 2;
    } else if(input == "4") {
        quitGame();
    } else {
        std::cout << "Invalid Input";
        createNewGame();
    }
    gameEngine->newGame(mode);
}

void MainMenu::loadSaveGame() {
    gameEngine->loadGame();
}

void MainMenu::printCredits() {
    std::cout << std::endl;
    std::cout << "----------------------------------" << std::endl;
    std::cout << "Name: Yonathan Kogan" << std::endl;
    std::cout << "Student ID: s3719826" << std::endl;
    std::cout << "Email: s3719826@student.rmit.edu.au" << std::endl;
    std::cout << "----------------------------------" << std::endl;
    std::cout << "Name: Ivan Bulosan" << std::endl;
    std::cout << "Student ID: s3720145" << std::endl;
    std::cout << "Email: s3720145@student.rmit.edu.au" << std::endl;
    std::cout << "----------------------------------" << std::endl;
    std::cout << "Name: Sheen Wey Chua" << std::endl;
    std::cout << "Student ID: s3795200" << std::endl;
    std::cout << "Email: s3795200@student.rmit.edu.au" << std::endl;
    std::cout << "----------------------------------" << std::endl;
    
    displayMenu();  
}

void MainMenu::quitGame() {
    gameEngine->~GameEngine();
    std::cout << "Goodbye" << std::endl;
    throw exception();
}
GameEngine* MainMenu::getGameEngine(){
    return gameEngine;
}