#include "../include/PenguinCannon.h"

PenguinCannon::PenguinCannon(GameObject& associated, GameObject * penguinBody)  : Component(associated) {
    Sprite * penguinCannonSprite;
    Collider * collider;
    pbody = penguinBody;
    angle = 0;
    collider = new Collider(associated);
    penguinCannonSprite = new Sprite(associated, "assets/img/cubngun.png");
    associated.AddComponent(shared_ptr<Component> (penguinCannonSprite));
    associated.AddComponent(shared_ptr<Component> (collider));
}

void PenguinCannon::Update(float dt) {
    Vect2 mouse;
    Vect2 goPos;
    double angleDeg;
    const float PI = 3.14159265;
    InputManager * input;
    timer.Update(dt);
    input = &InputManager::GetInstance();
    if(pbody == NULL) {
        associated.RequestedDelete();
    }
    associated.box.x = pbody->box.x + pbody->box.w / 2 - associated.box.w / 2;
    associated.box.y = pbody->box.y + pbody->box.h / 2 - associated.box.h / 2;
    mouse.x = input->GetMouseX() - Camera::pos.x;
    mouse.y = input->GetMouseY() - Camera::pos.y;
    goPos.x = associated.box.x;
    goPos.y = associated.box.y;
    direction = mouse - goPos;
    direction = direction.Normalize();
    angleDeg = acos(direction.x) * 180.0 / PI;
    if(direction.y < 0){
        angleDeg = angleDeg * -1;
    }
    associated.angleDeg = angleDeg;
    if(input->MousePress(LEFT_MOUSE_BUTTON)){
        Shoot(direction);
    }
}

void PenguinCannon::Render() {}

bool PenguinCannon::Is(string type) {
    bool result = false;
    if(type == "PenguinCannon") {
        result = true;
    }
    return result;
}

void PenguinCannon::Shoot(Vect2 direction) {
    cout<<"atirou"<<endl;
    GameObject * bulletGO;
    Game * instance;
    instance = &Game::GetInstance();
    Bullet * bullet;
    if(timer.Get() >= 1) {
        bulletGO = new GameObject();
        bulletGO->box.z = 1;
        bulletGO->box.x = associated.box.x + associated.box.w / 2 - bulletGO->box.w / 2;
        bulletGO->box.y = associated.box.y + associated.box.h / 2 - bulletGO->box.h / 2;
        bullet = new Bullet(*bulletGO, direction, 10, 10, 500, "assets/img/penguinbullet.png", 4);
        bulletGO->box.x = associated.box.x + associated.box.w / 2 - bulletGO->box.w / 2;
        bulletGO->box.y = associated.box.y + associated.box.h / 2 - bulletGO->box.h / 2;
        bulletGO->AddComponent(shared_ptr<Component> (bullet));
        instance->GetCurrentState().AddObject(bulletGO);
        timer.Restart();
    }
}