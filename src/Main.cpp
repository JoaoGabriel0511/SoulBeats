#include "../include/Game.h"
#include "../include/LevelState.h"
#include <iostream>
using namespace std;

int main() {
    cout << "Prestes a rodar o Jogo..." << endl;
    LevelState* levelState;
    levelState = new LevelState();
    Game::GetInstance().Push(levelState);
    Game::GetInstance().Run();
    return 0;
}