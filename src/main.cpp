#include "MainMenu.h"
#include "Test.h"
#include <iostream>
#include <string>

#define EXIT_SUCCESS 0

int main(int argc, char** argv) {
    MainMenu* mainMenu = new MainMenu();
    Test* testingMode = new Test();

    std::cout << "Welcome to Azul!" << std::endl;
    std::cout << "-------------------" << std::endl;

    if(argc == 3 && std::string(argv[1]) == "-t") {
        try{
            testingMode->readSaveFile(argv[2]);
        } catch(...) {
            testingMode->~Test();
        }
    }
    else{
        int seed;
        unsigned int randomSeed = atoi(argv[2]);
        if(argc == 3 && std::string(argv[1]) == "-s"){
            srand(randomSeed);
            seed = rand();
        }
        else{
            srand(time(NULL));
            seed = rand();
        }
        try {
            // std::cout << seed << "\n";
            // mainMenu->getGameEngine()->getInputProcessing()->setSeed(seed);
            mainMenu->getGameEngine()->getGameboard()->randomizeTileBag(seed, 0);
            mainMenu->displayMenu();
        } catch(...) {
            mainMenu->~MainMenu();
        }
    }

    return EXIT_SUCCESS;
}