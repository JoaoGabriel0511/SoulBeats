#include "MovingPlatforms.h"
#include "Game.h"
#include "../include/LevelState.h"

MovingPlatforms::MovingPlatforms(GameObject& associated, float velocity, bool moveX, bool moveY) : Component(associated) {
    this->movingX = moveX;
    this->movingY = moveY;
    this->velocity = velocity;
}

void MovingPlatforms::Start() {
    Sprite *platFormSprite;
    Collider *platFormCollider;
    platFormSprite = new Sprite(associated, PLATFORM_SPRITE);
    platFormSprite->SetScale({2,2});
    platFormCollider = new Collider(associated, {2,2}, {10, -70});
    switched = false;
}

bool MovingPlatforms::Is(string type) {
    bool result = false;
    if(type == "MovingPlatforms") {
        result = true;
    }
    return result;
}

void MovingPlatforms::Update(float dt) {
    if(global_beat->GetOnBeat()) {
        if(!switched) {
            velocity = -1 * velocity;
            switched = true;
        }
    } else {
        switched = false;
    }
    if(movingX) {
        associated.box.x += velocity * dt;
    }
    if(movingY){
        cout<<__FILE__<<"::"<<__LINE__<<endl;
        associated.box.y += velocity * dt;
    }
}