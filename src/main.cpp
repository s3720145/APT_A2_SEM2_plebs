#include "MainMenu.h"
#include "Test.h"
#include <iostream>
#include <string>

#define EXIT_SUCCESS 0

int main(int argc, char** argv) {
    MainMenu* mainMenu = new MainMenu();
    Test* testingMode = new Test();

    if(argc == 3 && std::string(argv[1]) == "-t") {
        try{
            testingMode->readSaveFile(argv[2]);
        } catch(...) {
            testingMode->~Test();
        }
    }
    else{
        try {
            mainMenu->displayMenu();
        } catch(...) {
            mainMenu->~MainMenu();
        }
    }

    return EXIT_SUCCESS;
}