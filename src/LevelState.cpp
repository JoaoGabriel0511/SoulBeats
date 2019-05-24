#include "../include/LevelState.h"

LevelState::LevelState() : State() {
    Start();
}

void LevelState::LoadAssets() {
    cout<<__FILE__<<__LINE__<<endl;

    // Level State Game Objects
    //// Background Game Object
    bg = new GameObject();
    Sprite *levelSprite;
    levelSprite = new Sprite(*bg, "assets/img/Sprite-0001.png");
    bg->box.h = Game::GetInstance().GetHeight();
    bg->box.w = Game::GetInstance().GetWidth();
    objectArray.emplace_back(bg);
    //// Beat Game Object
    beat = new GameObject();
    beat->box.x = 900;
    beat->box.y = 30;
    Beat* beat_component = new Beat(*beat);
    objectArray.emplace_back(beat);
    
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