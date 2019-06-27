#include "../include/Goal.h"

Goal::Goal(GameObject &associated) : Component(associated) {
    Start();
}

void Goal::Start() {
    goalSprite = new Sprite(associated, GOAL_SPRITE, GOAL_FRAME_COUNT, GOAL_FRAME_TIME);
    goalSprite->SetScale({2,2});
    Collider *collider;
    collider = new Collider(associated, {2, 2}, {-140, -60});
    charTochedIt = false;
    spiningTimer.Restart();
    updateSpriteTimes = 0;
}

void Goal::Update(float dt) {
    if(charTochedIt) {
        spiningTimer.Update(dt);
        if(spiningTimer.Get() >= GOAL_SPINING_TIME) {
            goalSprite->SwitchSprite(GOAL_SPRITE, GOAL_FRAME_COUNT, GOAL_QUICK_FRAME_TIME + GOAL_INCRESSE_TIME * updateSpriteTimes);
            updateSpriteTimes++;
            spiningTimer.Restart();
        }
    }
}

void Goal::Render() {}

bool Goal::Is(string type) {
    bool result = false;
    if(type == "Goal") {
        result = true;
    }
    return result;
}

void Goal::NotifyCollision (GameObject& other) {
    if(other.GetComponent("Character") != NULL) {
        if(!charTochedIt) {
            goalSprite->SwitchSprite(GOAL_SPRITE, GOAL_FRAME_COUNT, GOAL_QUICK_FRAME_TIME);
            updateSpriteTimes++;
            charTochedIt = true;
            ((LevelState*)  Game::GetInstance().GetCurrentStatePointer())->levelCompleted = true;
        }
    }
}