#include "../include/LevelState.h"

LevelState::LevelState() : State() {
    Start();
}

void LevelState::LoadAssets() {
    bg = new GameObject();
    GameObject* bellEnemyGO;
    BellEnemy* bellEnemy;
    Sprite *levelSprite;
    levelSprite = new Sprite(*bg, "assets/img/Sprite-0001.png");
    bg->box.h = Game::GetInstance().GetHeight();
    bg->box.w = Game::GetInstance().GetWidth();
    objectArray.emplace_back(bg);


    //ADICIONANDO INIMIGO

    bellEnemyGO = new GameObject();
    bellEnemy = new BellEnemy(*bellEnemyGO,10,10);
    bellEnemyGO->box.x = 100;
    bellEnemyGO->box.y = 500;
    objectArray.emplace_back(bellEnemyGO);

    //INIMIGO ADICIONADO
}

void LevelState::Pause() {

}

void LevelState::Resume() {

}

void LevelState::Update(float dt) {
    State::Update(dt);
    if(InputManager::GetInstance().QuitRequested()){
        quitRequested = true;
    }
}