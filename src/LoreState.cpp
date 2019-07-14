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
    GameObject* bg2 = new GameObject();
    Sprite* bg2Sprite = new Sprite(*bg2, "assets/img/background/Sprite-0001.png");
    bg2->box.w = GameInfo::GetInstance().WIDTH;
    bg2->box.h = GameInfo::GetInstance().HEIGHT;
    bg2->box.z = 1;
    bg2->box.x = 0;
    bg2->box.y = 0;
    objectArray.emplace_back(bg);
    objectArray.emplace_back(bg2);
    /*Camera::pos.x = 0;
    Camera::pos.y = 0;*/
}

void LoreState::Update(float dt) {
    State::Update(dt);
    if(InputManager::GetInstance().KeyPress(SDLK_RETURN)){
        popRequested = true;
    }
}