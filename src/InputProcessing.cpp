#include "InputProcessing.h"
#include <iostream>

InputProcessing::InputProcessing() {
    numValidTurns = 0;
}

InputProcessing::~InputProcessing() {

}

bool InputProcessing::processPlayerInput(string playerInput, Gameboard* gameboard) {
    bool isValidTurn = true;
    vector<std::string> tokens;
    string token;
    int numTokens = 0;
    std::istringstream tokenStream(playerInput);

    // splits string into tokens and place into vector
    while (getline(tokenStream, token, ' ')) {
        tokens.push_back(token);
        numTokens++;
    }

    if(numTokens != 1 && numTokens != 2 && numTokens != 4) {
        isValidTurn = false;
    } else if(numTokens == 1) {
        if(tokens[0] == "quit") {
            throw std::exception();
        } else {
            isValidTurn = false;
        }
    } else if(numTokens == 2) {
        if(tokens[0] == "save") {
            saveGame(tokens[2], gameboard);
        } else {
            isValidTurn = false;
        }
    } else if(tokens[0] == "turn") {
        int factory_row = std::stoi(tokens[1]);
        int storage_row = std::stoi(tokens[3]);

        if((factory_row >= 0 && factory_row <= 5) && (storage_row >= 1 && storage_row <= 5) && isAColour(*tokens[2].c_str())) {
            isValidTurn = gameboard->FactoryTilesToPlayer(factory_row, storage_row, static_cast<Colour>(*tokens[2].c_str()));
        } else {
            isValidTurn = false;
        }

        if(isValidTurn == true) {
            validTurns.push_back(playerInput);
            ++numValidTurns;
        }
    } else {
        isValidTurn = false;
    }
    return isValidTurn;
}

// TODO
void InputProcessing::saveGame(string fileName, Gameboard* gameboard) {
    std::ofstream saveFile("src/saveFiles/" + fileName);
    std::ifstream tileBag("src/DefaultTileBag.txt");
    string content;

    // getline(tileBag, content);
    // content.erase(content.end() - 1);
    // saveFile << content << '\n';

    // content = gameboard->playerNamesToString();
    // saveFile << content;

    // for(int i = 0; i < numValidTurns; ++i) {
    //     saveFile << validTurns[numValidTurns] << '\n';
    // }
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