#include "../include/LoreState.h"

LoreState::LoreState(string bgSpriteFile) : State() {
    this->bgSpriteFile = bgSpriteFile;
}

void LoreState::LoadAssets(){
    GameObject* bg = new GameObject();
    Sprite* bgSprite = new Sprite(*bg, bgSpriteFile);
    bg->box.w = GameInfo::GetInstance().WIDTH;
    bg->box.h = GameInfo::GetInstance().HEIGHT;
    bg->box.z = 2;
    bg->box.x = 0;
    bg->box.y = 0;
    objectArray.emplace_back(bg);
    /*Camera::pos.x = 0;
    Camera::pos.y = 0;*/
}

void LoreState::Update(float dt) {
    State::Update(dt);
    if(InputManager::GetInstance().KeyPress(SDLK_RETURN)){
        popRequested = true;
    }
}