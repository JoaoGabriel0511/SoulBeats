#include "../include/InitialScreenState.h"

InitialScreenState::InitialScreenState() : State() {
}


void InitialScreenState::Start() {
    floorOnInitialState = true;
    State::Start();
}

void InitialScreenState::LoadAssets() {
    // Background
    backgroundGo = new GameObject();
    backgroundGo->box.w = GameInfo::GetInstance().WIDTH;
    backgroundGo->box.h = GameInfo::GetInstance().HEIGHT;
    backgroundGo->box.x = Camera::pos.x;
    backgroundGo->box.y = Camera::pos.y;
    Sprite* backgroungSprite = new Sprite(*backgroundGo, INITIAL_SCREEN_BACKGROUND_SPRITE);
    backgroungSprite->SetScale({2.1,2.1});

    Music * menuMusic = new Music(*backgroundGo, INTIAL_SCREEN_MUSIC);

    // Floor
    floorGo = new GameObject();
    floorGo->box.x = Camera::pos.x;
    floorGo->box.y = Camera::pos.y;
    floorSprite = new Sprite(*floorGo, INITIAL_SCREEN_FLOOR_1_SPRITE);
    floorSprite->SetScale({2.1, 2.1});

    // Heart
    heartGo = new GameObject();
    heartGo->box.x = Camera::pos.x + 230;
    heartGo->box.y = Camera::pos.y + 120;
    Sprite * heartSprite = new Sprite(*heartGo, MENU_HEART_SPRITE);
    heartSprite->SetScale({1.2, 1.2});

    // Aria
    characterGo = new GameObject();
    characterGo->box.x = Camera::pos.x + 435;
    characterGo->box.y = Camera::pos.y + 360;
    characterGo->box.z = 3;
    characterSprite = new Sprite(*characterGo, MENU_CHARACTER_SPRITE_SHEET, 4, MENU_CHARACTER_FRAME_TIME, 0);
    characterSprite->SetScale({1.4, 1.4});


    // Highlight
    highlightGo = new GameObject();
    highlightGo->box.x = Camera::pos.x + 180;
    highlightGo->box.y = Camera::pos.y + 140;
    highlightGo->box.z = 2;
    highlightSprite = new Sprite(*highlightGo, MENU_HIGHLIGHT_SPRITE_1);
    highlightSprite->SetScale({1.4, 1.4});


    objectArray.emplace_back(backgroundGo);
    objectArray.emplace_back(floorGo);
    objectArray.emplace_back(heartGo);
    objectArray.emplace_back(characterGo); 
    objectArray.emplace_back(highlightGo);

}

void InitialScreenState::Update(float dt) {
    State::Update(dt);
    floorChangeTimer.Update(dt);
    if(floorChangeTimer.Get() > FLOOR_CHANGE_INTERVAL){
        if(floorOnInitialState){
            floorSprite->SwitchSprite(INITIAL_SCREEN_FLOOR_2_SPRITE, 1, 0);
            highlightSprite->SwitchSprite(MENU_HIGHLIGHT_SPRITE_2, 1, 0);
            floorOnInitialState = false;
        } 
        else {
            floorSprite->SwitchSprite(INITIAL_SCREEN_FLOOR_1_SPRITE, 1, 0);
            highlightSprite->SwitchSprite(MENU_HIGHLIGHT_SPRITE_1, 1, 0);
            floorOnInitialState = true;
        }
        floorChangeTimer.Restart();
    }

}

void InitialScreenState::Pause() {}

void InitialScreenState::Resume() {}

void InitialScreenState::StartData() {}