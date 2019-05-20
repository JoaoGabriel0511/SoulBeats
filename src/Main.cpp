#include "../include/Game.h"
#include "../include/StageState.h"
#include "../include/TitleState.h"
#include <iostream>
using namespace std;

int main() {
    cout << "Prestes a rodar o Jogo..." << endl;
    TitleState* titleState;
    titleState = new TitleState();
    Game::GetInstance().Push(titleState);
    Game::GetInstance().Run();
    return 0;
}