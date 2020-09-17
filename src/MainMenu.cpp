#include "MainMenu.h"
#include <iostream>

using std::exception;

MainMenu::MainMenu() {

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

void MainMenu::createNewGame() {

}

void MainMenu::loadSaveGame() {

}

void MainMenu::testingMode() {

}

void MainMenu::printCredits() {
    std::cout << std::endl;
    std::cout << "----------------------------------" << std::endl;
    std::cout << "Name: <full name>" << std::endl;
    std::cout << "Student ID: <student number>" << std::endl;
    std::cout << "Email: <email address>" << std::endl;
    std::cout << "----------------------------------" << std::endl;
    std::cout << "Name: <full name>" << std::endl;
    std::cout << "Student ID: <student number>" << std::endl;
    std::cout << "Email: <email address>" << std::endl;
    std::cout << "----------------------------------" << std::endl;
    std::cout << "Name: <full name>" << std::endl;
    std::cout << "Student ID: <student number>" << std::endl;
    std::cout << "Email: <email address>" << std::endl;
    std::cout << "----------------------------------" << std::endl;
    
    displayMenu();  
}

void MainMenu::prompt() {
    std::string input;
    std::cout << std::endl << "> ";
    std::cin >> input;
    if(std::cin.eof() == true || input == "4"){
        std::cout << "Goodbye" << std::endl;
    }
    else if(input == "1"){
        //TODO
    }
    else if(input == "2"){
        //TODO
    }
    else if(input == "3"){
        printCredits();
    }
    else{
        std::cout << "Invalid Input";
        prompt();
     }
}

void MainMenu::quitGame() {
    //throw exception();
}