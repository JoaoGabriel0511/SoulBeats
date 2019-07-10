#include "../include/Heart.h"

Heart::Heart(GameObject& associated, int index) : Component(associated) {
    this->index = index;
}

void Heart::Start() {
    heartSprite = new Sprite(associated, HEART_SPRITE);
    heartSprite->SetScale({2,2});
    heartCollider = new Collider(associated, {2,2}, {-40, -40});
}

bool Heart::Is(string type) {
    bool result = false;
    if(type == "Heart") {
        result = true;
    }
    return result;
}

void Heart::NotifyCollision(GameObject& other) {
    if(other.GetComponent("Character") != NULL){
        LevelData::GetInstance().heartData[index]->wasCollected = true;
        associated.RequestedDelete();
    }
}

