#include "../include/Game.h"
#include "../include/LevelState.h"
#include "../include/InitialScreenState.h"
#include <iostream>
using namespace std;

int main() {
    cout << "Prestes a rodar o Jogo..." << endl;
    LevelState* levelState;
    levelState = new LevelState();
    InitialScreenState* menu;
    menu = new InitialScreenState();

    Game::GetInstance().Push(levelState);
    Game::GetInstance().Run();
    return 0;
}