#include "../include/LevelState.h"
#include "Game.h"

LevelState::LevelState() : State() {
    Start();
}

void LevelState::LoadAssets() {
    //Adicionando Background

    bg = new GameObject();
    GameObject* bellEnemyGO;
    BellEnemy* bellEnemy;
    Sprite *levelSprite;
    levelSprite = new Sprite(*bg, "assets/img/background/Sprite-0001.png");
    bg->box.h = Game::GetInstance().GetHeight();
    bg->box.w = Game::GetInstance().GetWidth();
    objectArray.emplace_back(bg);
    //// Beat Game Object
    beat = new GameObject();
    beat->box.x = 900;
    beat->box.y = 30;
    Beat* beat_component = new Beat(*beat);
    global_beat = beat_component;
    objectArray.emplace_back(beat);

    //Adicionando Personagem

    GameObject * characterGO;
    characterGO = new GameObject();
    characterGO->box.x = 200;
    characterGO->box.y = 500;
    characterGO->box.z = 1;
    new Character(*characterGO);
    objectArray.emplace_back(characterGO);

    //Personagem Adicionado

    //Adicionando Inimigo

    bellEnemyGO = new GameObject();
    bellEnemy = new BellEnemy(*bellEnemyGO,10,10,characterGO);
    bellEnemyGO->box.x = 100;
    bellEnemyGO->box.y = 537;
    objectArray.emplace_back(bellEnemyGO);
    
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

GameObject* LevelState::GetBeatObject(){
    return this->beat;
}