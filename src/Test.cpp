#include "GameEngine.h"
#include "GenericLinkedList.cpp"
#include "Test.h"

template class GenericLinkedList<Player*>;
template class GenericLinkedList<Tile*>;
template class GenericNode<Player*>;
template class GenericNode<Tile*>;

Test::Test(){
    tileBag = new GenericLinkedList<Tile*>();
    players = new GenericLinkedList<Player*>();
    loadSaveFile();
}

Test::readSaveFile(){
    readTileBag();
}

Test::readTileBag(){
    char readIn;
    for(int i = 0; i < tileBagSize; i++){
        std::cin >> readIn;
        tileBag->addToBack(readIn);
    }
}
Test::readTurn(){
    
}