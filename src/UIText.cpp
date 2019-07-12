#include "../include/UIText.h"

UIText::UIText(GameObject& associated, Vect2 pos, string iconFile) : Component(associated) {
    this->pos = pos;
    iconGO = new GameObject();
    iconGO->box.z = 7;
    iconSprite = new Sprite(*iconGO, iconFile);
    iconSprite->SetScale({1,1});
    Game::GetInstance().GetCurrentState().AddObject(iconGO);
}

UIText::~UIText(){
    iconGO->RequestedDelete();
}

bool UIText::Is(string type) {
    bool result = false;
    if(type == "UIText") {
        result = true;
    }
    return result;
}

void UIText::Start() {
    text = new Text(associated, FONT, 20, Text::TextStyle::SOLID, "0", SDL_Color {255,255,255}, 0);
}

void UIText::Update(float dt) {
    Camera::Update(dt);
    associated.box.x = pos.x - Camera::pos.x;
    associated.box.y = pos.y - Camera::pos.y;
    iconGO->box.x = pos.x - 40 - Camera::pos.x;
    iconGO->box.y = pos.y - 10 - Camera::pos.y;
}

void UIText::UpdateText(string value) {
    text->SetText("- " + value);
}