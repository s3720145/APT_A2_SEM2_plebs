#include "InputProcessing.h"
#include <iostream>

InputProcessing::InputProcessing() {
    numValidTurns = ZERO;
}

InputProcessing::~InputProcessing() {

}

bool InputProcessing::processPlayerInput(
    string playerInput, Gameboard* gameboard) {
    bool isValidTurn = true;
    vector<std::string> tokens;
    string token;
    int numTokens = ZERO;
    std::istringstream tokenStream(playerInput);

    // splits string into tokens and place into vector
    while (getline(tokenStream, token, ' ')) {
        tokens.push_back(token);
        numTokens++;
    }

    if(numTokens != ONE && numTokens != TWO && numTokens != FOUR) {
        isValidTurn = false;
    } else if(numTokens == ONE) {
        if(tokens[ZERO] == "quit") {
            throw std::exception();
        } else {
            isValidTurn = false;
        }
    } else if(numTokens == TWO) {
        if(tokens[ZERO] == "save") {
            saveGame(tokens[ONE], gameboard);
            std::cout << "Game sucessfully saved to - " << tokens[ONE] <<
             std::endl;
            isValidTurn = false;
        } else {
            isValidTurn = false;
        }
    } else if(tokens[ZERO] == "turn") {
        int factory_row = std::stoi(tokens[ONE]);
        int storage_row = std::stoi(tokens[THREE]);

        if(factory_row == ZERO && gameboard->getIsFirstTurn() == true) {
            std::cout << "Invalid move - Cannot take from factory 
            0 in first turn" << std::endl;
            isValidTurn = false;
        } else {
            if((factory_row >= ZERO && factory_row <= MAX_FACTORY) && (
                storage_row >= MIN_STORAGE_ROW && storage_row <= MAX_STORAGE_ROW
                ) && isAColour(*tokens[TWO].c_str())) {
                isValidTurn = gameboard->FactoryTilesToPlayer(
                    factory_row, storage_row, static_cast<Colour>(
                        *tokens[TWO].c_str()));
            } else {
                isValidTurn = false;
            }

            if(isValidTurn == true) {
                if(gameboard->getIsFirstTurn() == true) {
                    gameboard->setIsFirstTurn(false);
                }
                validTurns.push_back(playerInput);
                ++numValidTurns;
            }
        }

    } else {
        isValidTurn = false;
    }

    return isValidTurn;
}

// TODO
void InputProcessing::saveGame(string fileName, Gameboard* gameboard) {
    std::ofstream saveFile("src/saveFiles/" + fileName);
    string content;

    if(saveFile.fail()) {
        std::cout << "file not found" << std::endl;
    } else {
        std::ifstream file("src/DefaultTileBag.txt");
        string defaultTileBag;

        getline(file, defaultTileBag);

        saveFile << defaultTileBag << '\n';

        content = gameboard->playerNamesToString();

        saveFile << content;

        for(int i = ZERO; i < numValidTurns; ++i) {
            saveFile << validTurns[i] << '\n';
        }

        file.close();
    }

    saveFile.close();
}

bool InputProcessing::isAColour(char c) {
    bool isColour = false;

    if(c == 'B') {
        isColour = true;
    } else if(c == 'Y') {
        isColour = true;
    } else if(c == 'R') {
        isColour = true;
    } else if(c == 'U') {
        isColour = true;
    } else if(c == 'L') {
        isColour = true;
    }

    return isColour;
}