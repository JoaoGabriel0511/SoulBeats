#include "../include/VictoryState.h"

VictoryState::VictoryState() : State() {
}

void VictoryState::Start() {
    State::Start();
}

void VictoryState::LoadAssets() {
    // Adicionando Background
    bg = new GameObject();
    Camera::pos.x = 0;
    Camera::pos.y = 0;
    Camera::UnFollow();
    new Sprite(*bg, VICTORY_BG_SPRITE);
    music = new Music(*bg, VICTORY_BG_MUSIC);
    music->Play(-1);
    bg->box.w = GameInfo::GetInstance().WIDTH;
    bg->box.h = GameInfo::GetInstance().HEIGHT;
    objectArray.emplace_back(bg);
    // Background Adicionado
}

void VictoryState::Pause() {}

void VictoryState::Resume() {}