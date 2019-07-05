#include "../include/Launcher.h"

Launcher::Launcher(GameObject& associated, LauncherType type, GameObject* character) : Component(associated) {
    this->type = type;
    this->character = character;
}

void Launcher::Start() {
    switch (type) {
        case UP:
            launcherSprite = new Sprite(associated, LAUNCHER_UP);
            pointPos = {associated.box.x - 3 * associated.box.w, associated.box.y - (character->box.h)};
            break;
        case UP_RIGHT:
            launcherSprite = new Sprite(associated, LAUNCHER_UP_RIGHT);
            pointPos = {associated.box.x + associated.box.w, associated.box.y - (character->box.h)};
            break;
        case UP_LEFT:
            launcherSprite = new Sprite(associated, LAUNCHER_UP_LEFT);
            pointPos = {associated.box.x - character->box.w, associated.box.y - (character->box.h)};
            break;
        case RIGHT:
            launcherSprite = new Sprite(associated, LAUNCHER_RIGHT);
            pointPos = {associated.box.x + associated.box.w, associated.box.y + associated.box.h/2 - (character->box.h/2)};
            break;
        case LEFT:
            launcherSprite = new Sprite(associated, LAUNCHER_LEFT);
            pointPos = {associated.box.x - 2*character->box.w, associated.box.y + associated.box.h/2 - (character->box.h/2)};
            break;
        case DOWN:
            launcherSprite = new Sprite(associated, LAUNCHER_DOWN);
            pointPos = {associated.box.x - 3 * associated.box.w, associated.box.y + associated.box.h};
            break;
        default:
            break;
    }
    launcherSprite->SetScale({2,2});
    launcherCollider = new Collider(associated, {2,2}, {0, 0});
}

void Launcher::NotifyCollision(GameObject& other) {
    if(other.GetComponent("Attack") != NULL) {
        cout<<"PointPos.y "<<pointPos.y<<endl;
        character->box.x = pointPos.x;
        character->box.y = pointPos.y - (character->box.h);
        //character->Update(0);
        ((Character*) character->GetComponent("Character").get())->LaunchCharacter({0,0},true);
    }
}

void Launcher::Update(float dt) {
    this->dt = dt;
}

bool Launcher::Is(string type) {
    bool result = false;
    if(type == "Launcher") {
        result = true;
    }
    return result;
}