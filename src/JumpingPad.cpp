#include "../include/JumpingPad.h"

JumpingPad::JumpingPad(GameObject& associated, GameObject* character) : Component(associated) {
    this->character = character;
}

void JumpingPad::Start() {
    padSprite = new Sprite(associated, JUMPING_PAD_SPRITE);
    padSprite->SetScale({3,3});
    padCollider = new Collider(associated, {2,2}, {10, -70});
}

void JumpingPad::NotifyCollision(GameObject& other) {
    // cout << "JumpingPad collision detected.\n";
    // if(other.GetComponent("Attack") != NULL) {
        // cout<<"PointPos.y "<<pointPos.y<<endl;
        // character->box.x = pointPos.x;
        // character->box.y = pointPos.y - (character->box.h);
        // //character->Update(0);
        // ((Character*) character->GetComponent("Character").get())->LaunchCharacter({0,0},true);
    // }
}

void JumpingPad::Update(float dt) {
}

bool JumpingPad::Is(string type) {
    return (type == "JumpingPad") ? true : false;
}