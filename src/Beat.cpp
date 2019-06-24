#include "../include/Beat.h"

Beat::Beat(GameObject& associated, GameObject* heartBackground) : Component(associated){
    this->heartBackground = heartBackground;
    Start();
}

void Beat::Start(){
    beatSprite = new Sprite(associated, BEATING_HEART_SPRITE, FRAME_COUNT, BEAT_TRUE_LIMIT/FRAME_COUNT);
    onBeat = true;
}

void Beat::Update(float dt){
    associated.box.x = 900 - Camera::pos.x;
    associated.box.y = 30 - Camera::pos.y;
    heartBackground->box.x = 877 - Camera::pos.x;
    heartBackground->box.y = 28 - Camera::pos.y;
    if(onBeat){
        if(trueTimer.Get() >= BEAT_TRUE_LIMIT){
            onBeat = false;
            beatSprite->SwitchSprite(IDLE_HEART_SPRITE, STILL_FRAME_COUNT, 1);
            trueTimer.Restart();
        }
        trueTimer.Update(dt);
    } else {
        if(falseTimer.Get() >= BEAT_FALSE_LIMIT){
            onBeat = true;
            beatSprite->SwitchSprite(BEATING_HEART_SPRITE, FRAME_COUNT, BEAT_TRUE_LIMIT/FRAME_COUNT);
            falseTimer.Restart();
        }
        falseTimer.Update(dt);
    }
}

void Beat::Render(){}


bool Beat::Is(string type){
    return (type == "Beat") ? true : false;
}

bool Beat::GetOnBeat(){
    // if(onBeat == true) cout << "returning true\n;"; else cout << "returning false\n;";
    return onBeat;
}