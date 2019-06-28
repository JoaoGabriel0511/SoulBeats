#include "../include/Attack.h"

Attack::Attack(GameObject &associated, Vect2 scale, Vect2 offset, GameObject *attackOrigin, int width, int height, float offsetX, float offsetY) : Component(associated){
    Collider *collider = new Collider(associated, scale, offset);
    this->attackOrigin = attackOrigin;
    associated.box.h = height;
    associated.box.w = width;
    this->offsetX = offsetX;
    this->offsetY = offsetY;
}

void Attack::Update(float dt){
    associated.box.x = attackOrigin->box.x + offsetX;
    associated.box.y = attackOrigin->box.y + offsetY;
}

void Attack::NotifyCollision(GameObject &other) {
}

void Attack::Render(){
}

void Attack::Start(){
}

bool Attack::Is(string type){
    bool result = false;
    if (type == "Attack")
    {
        result = true;
    }
    return result;
}

Attack::~Attack() {
    this->attackOrigin = nullptr;
}