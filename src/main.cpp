#include "MainMenu.h"
#include "Test.h"
#include <iostream>

#define EXIT_SUCCESS 0

int main(int argc, char** argv) {
    MainMenu* mainMenu = new MainMenu();
    Test* testingMode = new Test();

    std::cout << "Welcome to Azul!" << std::endl;
    std::cout << "-------------------" << std::endl;
    
    try {
        mainMenu->displayMenu();
    } catch(...) {
        mainMenu->~MainMenu();
    }

    try{
        
    } catch(...) {
        mainMenu->~MainMenu();
    }

    return EXIT_SUCCESS;
}