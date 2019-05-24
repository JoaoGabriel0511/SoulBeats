#include "../include/Beat.h"

Beat::Beat(GameObject& associated) : Component(associated){
    Start();
}

void Beat::Start(){
    beatSprite = new Sprite(associated, BEATING_HEART_SPRITE, FRAME_COUNT, FRAME_TIME);
    onBeat = true;
}

void Beat::Update(float dt){
    if(onBeat){
        if(trueTimer.Get() >= BEAT_LIMIT){
            onBeat = false;
            beatSprite->SwitchSprite(IDLE_HEART_SPRITE, STILL_FRAME_COUNT, FRAME_TIME);
            trueTimer.Restart();
        }
        cout << "ON TIME\n";
        trueTimer.Update(dt);
    } else {
        if(falseTimer.Get() >= BEAT_INTERVAL){
            onBeat = true;
            beatSprite->SwitchSprite(BEATING_HEART_SPRITE, FRAME_COUNT, FRAME_TIME);
            falseTimer.Restart();
        }
        cout << "[NOT] on time\n";
        falseTimer.Update(dt);
    }
}

void Beat::Render(){}


bool Beat::Is(string type){
    return (type == "Beat") ? true : false;
}